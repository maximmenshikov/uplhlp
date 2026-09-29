#include "stdafx.h"
#include "PolicyMsgQueue.h"

//#define RUNNING_IN_POLICYENGINE

// queue handle that we won't close so that it can be accessed system-wide.
static HANDLE hPolicyMsgQueue = NULL;
static HANDLE hPolicyMsgQueueEvent = NULL;

/**
 * Open the shared read queue and its event once, when built as part of the
 * policy engine (guarded by RUNNING_IN_POLICYENGINE).
 */
static inline void
EnsureQueueIsCreated()
{
#ifdef RUNNING_IN_POLICYENGINE
    if (hPolicyMsgQueue == NULL)
        hPolicyMsgQueue = GetPolicyMsgQueue(FALSE);
    if (hPolicyMsgQueueEvent == NULL)
        hPolicyMsgQueueEvent = GetPolicyMsgQueueEvent();
#endif
}

/**
 * Create (or open) the named policy message queue.
 *
 * @param writeOrRead    Passed as the queue's read-access flag: TRUE opens the
 *                       queue for reading, FALSE for writing.
 *
 * @return Handle to the message queue, or NULL on failure.
 */
HANDLE
GetPolicyMsgQueue(BOOL writeOrRead)
{
    MSGQUEUEOPTIONS opt;
    opt.dwSize = sizeof(MSGQUEUEOPTIONS);
    opt.dwFlags = MSGQUEUE_NOPRECOMMIT | MSGQUEUE_ALLOW_BROKEN;
    opt.dwMaxMessages = 0;
    opt.cbMaxMessage = sizeof(FULLUNLOCK_POLICY_MESSAGE);
    opt.bReadAccess = writeOrRead;
    HANDLE hMsgQueue = CreateMsgQueue(MSGQUEUE_NAME, &opt);
    return hMsgQueue;
}

/**
 * Create (or open) the named event associated with the policy message queue.
 *
 * @return Handle to the event.
 */
HANDLE
GetPolicyMsgQueueEvent()
{
    return CreateEvent(NULL, FALSE, FALSE, MSGQUEUE_EVENT_NAME);
}

static FULLUNLOCK_POLICY_MESSAGE previousMsg = {ACCESS_DENIED, L"", L""};

/**
 * Post a policy message to the queue, skipping it if it duplicates the
 * previous message (same type and account).
 *
 * @param msg    Policy message to post.
 */
void
PolicyMsgQueue_Write(FULLUNLOCK_POLICY_MESSAGE msg)
{
    /* double-guard */
    if (previousMsg.type != msg.type ||
        memcmp(&previousMsg.userAccount, &msg.userAccount,
               sizeof(wchar_t) * 200) != 0)
    {
        memcpy(&previousMsg, &msg, sizeof(FULLUNLOCK_POLICY_MESSAGE));

        EnsureQueueIsCreated();

        HANDLE hQueue = GetPolicyMsgQueue(FALSE);
        WriteMsgQueue(hQueue, &msg, sizeof(FULLUNLOCK_POLICY_MESSAGE), INFINITE,
                      0);
        CloseHandle(hQueue);
    }
}
