#ifndef _G3DKMD_WAIT_QUEUE_H_
#define _G3DKMD_WAIT_QUEUE_H_

#if defined(linux) && !defined(linux_user_mode)   // linux kernel
// headers
  #include <linux/wait.h>

// structs

typedef wait_queue_head_t g3dkmd_wait_queue_head_t;

// macros
  #define g3dkmd_init_waitqueue_head(wq) \
            init_waitqueue_head(wq)

  #define g3dkmd_wait_event_interruptible_timeout(wq, condition, timeout) \
            wait_event_interruptible_timeout(wq, condition, msecs_to_jiffies(timeout))

  #define g3dkmd_wait_event_interruptible(wq, condition) \
            wait_event_interruptible(wq, condition)

  #define g3dkmd_wake_up_interruptible(wq) \
            wake_up_interruptible(wq)

#else // WIN or linux_user
// headers


// structs

typedef int g3dkmd_wait_queue_head_t;

// macros
  #define ERESTARTSYS     512


  // do nothing
  #define g3dkmd_init_waitqueue_head(wq) 

  // assume condition alway true, release without wait.
  #define g3dkmd_wait_event_interruptible_timeout(wq, condition, timeout) 1
  // assume condition always true.
  #define g3dkmd_wait_event_interruptible(wq, condition) 0
  // do nohting
  #define g3dkmd_wake_up_interruptible(wq) 
#endif



// prototypes



#endif  // _G3DKMD_WAIT_QUEUE_H_
