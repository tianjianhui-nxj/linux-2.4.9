/*
 *  Copyright (c) 2000-2001 LSI Logic Corporation.
 *
 *
 *           Name:  MPI_TARG.H
 *          Title:  MPI Target mode messages and structures
 *  Creation Date:  June 22, 2000
 *
 *    MPI Version:  01.01.03
 *
 *  Version History
 *  ---------------
 *
 *  Date      Version   Description
 *  --------  --------  ------------------------------------------------------
 *  05-08-00  00.10.01  Original release for 0.10 spec dated 4/26/2000.
 *  06-06-00  01.00.01  Update version number for 1.0 release.
 *  06-22-00  01.00.02  Added _MSG_TARGET_CMD_BUFFER_POST_REPLY structure.
 *                      Corrected DECSRIPTOR typo to DESCRIPTOR.
 *  11-02-00  01.01.01  Original release for post 1.0 work
 *                      Modified target mode to use IoIndex instead of
 *                      HostIndex and IocIndex. Added Alias.
 *  01-09-01  01.01.02  Added defines for TARGET_ASSIST_FLAGS_REPOST_CMD_BUFFER
 *                      and TARGET_STATUS_SEND_FLAGS_REPOST_CMD_BUFFER.
 *  02-20-01  01.01.03  Started using MPI_POINTER.
 *                      Added structures for MPI_TARGET_SCSI_SPI_CMD_BUFFER and
 *                      MPI_TARGET_FCP_CMD_BUFFER.
 *  --------------------------------------------------------------------------
 */

#ifndef MPI_TARG_H
#define MPI_TARG_H


/******************************************************************************
*
*        S C S I    T a r g e t    M e s s a g e s
*
*******************************************************************************/

typedef struct _CMD_BUFFER_DESCRIPTOR
{
    U16                     IoIndex;
    U16                     Reserved;
    union
    {
        U32                 PhysicalAddress32;
        U64                 PhysicalAddress64;
    } u;
} CMD_BUFFER_DESCRIPTOR, MPI_POINTER PTR_CMD_BUFFER_DESCRIPTOR,
  CmdBufferDescriptor_t, MPI_POINTER pCmdBufferDescriptor_t;


/****************************************************************************/
/* Target Command Buffer Post Request                                       */
/****************************************************************************/

typedef struct _MSG_TARGET_CMD_BUFFER_POST_REQUEST
{
    U8                      BufferPostFlags;
    U8                      BufferCount;
    U8                      ChainOffset;
    U8                      Function;
    U8                      BufferLength;
    U8                      Reserved;
    U8                      Reserved1;
    U8                      MsgFlags;
    U32                     MsgContext;
    CMD_BUFFER_DESCRIPTOR   Buffer[1];
} MSG_TARGET_CMD_BUFFER_POST_REQUEST, MPI_POINTER PTR_MSG_TARGET_CMD_BUFFER_POST_REQUEST,
  TargetCmdBufferPostRequest_t, MPI_POINTER pTargetCmdBufferPostRequest_t;

#define CMD_BUFFER_POST_FLAGS_PORT_MASK         (0x01)
#define CMD_BUFFER_POST_FLAGS_ADDR_MODE_MASK    (0x80)
#define CMD_BUFFER_POST_FLAGS_ADDR_MODE_32      (0)
#define CMD_BUFFER_POST_FLAGS_ADDR_MODE_64      (1)
#define CMD_BUFFER_POST_FLAGS_64_BIT_ADDR       (0x80)

#define CMD_BUFFER_POST_IO_INDEX_MASK           (0x00003FFF)


typedef struct _MSG_TARGET_CMD_BUFFER_POST_REPLY
{
    U8                      BufferPostFlags;
    U8                      BufferCount;
    U8                      MsgLength;
    U8                      Function;
    U8                      BufferLength;
    U8                      Reserved;
    U8                      Reserved1;
    U8                      MsgFlags;
    U32                     MsgContext;
    U16                     Reserved2;
    U16                     IOCStatus;
    U32                     IOCLogInfo;
} MSG_TARGET_CMD_BUFFER_POST_REPLY, MPI_POINTER PTR_MSG_TARGET_CMD_BUFFER_POST_REPLY,
  TargetCmdBufferPostReply_t, MPI_POINTER pTargetCmdBufferPostReply_t;


typedef struct _MSG_PRIORITY_CMD_RECEIVED_REPLY
{
    U16                     Reserved;
    U8                      MsgLength;
    U8                      Function;
    U16                     Reserved1;
    U8                      Reserved2;
    U8                      MsgFlags;
    U32                     MsgContext;
    U8                      PriorityReason;
    U8                      Reserved3;
    U16                     IOCStatus;
    U32                     IOCLogInfo;
    U32                     ReplyWord;
} MSG_PRIORITY_CMD_RECEIVED_REPLY, MPI_POINTER PTR_MSG_PRIORITY_CMD_RECEIVED_REPLY,
  PriorityCommandReceivedReply_t, MPI_POINTER pPriorityCommandReceivedReply_t;

#define PRIORITY_REASON_NO_DISCONNECT           (0x00)
#define PRIORITY_REASON_SCSI_TASK_MANAGEMENT    (0x01)
#define PRIORITY_REASON_UNKNOWN                 (0xFF)


typedef struct _MSG_TARGET_CMD_BUFFER_POST_ERROR_REPLY
{
    U16                     Reserved;
    U8                      MsgLength;
    U8                      Function;
    U16                     Reserved1;
    U8                      Reserved2;
    U8                      MsgFlags;
    U32                     MsgContext;
    U16                     Reserved3;
    U16                     IOCStatus;
    U32                     IOCLogInfo;
    U32                     ReplyWord;
} MSG_TARGET_CMD_BUFFER_POST_ERROR_REPLY,
  MPI_POINTER PTR_MSG_TARGET_CMD_BUFFER_POST_ERROR_REPLY,
  TargetCmdBufferPostErrorReply_t, MPI_POINTER pTargetCmdBufferPostErrorReply_t;


typedef struct _MPI_TARGET_FCP_CMD_BUFFER
{
    U8      FcpLun[8];
    U8      FcpCntl[4];
    U8      FcpCdb[16];
    U32     FcpDl;
} MPI_TARGET_FCP_CMD_BUFFER, MPI_POINTER PTR_MPI_TARGET_FCP_CMD_BUFFER,
  MpiTargetFcpCmdBuffer, MPI_POINTER pMpiTargetFcpCmdBuffer;


typedef struct _MPI_TARGET_SCSI_SPI_CMD_BUFFER
{
    /* SPI L_Q information unit */
    U8      L_QType;
    U8      Reserved;
    U16     Tag;
    U8      LogicalUnitNumber[8];
    U32     DataLength;
    /* SPI command information unit */
    U8      ReservedFirstByteOfCommandIU;
    U8      TaskAttribute;
    U8      TaskManagementFlags;
    U8      AdditionalCDBLength;
    U8      CDB[16];
} MPI_TARGET_SCSI_SPI_CMD_BUFFER,
  MPI_POINTER PTR_MPI_TARGET_SCSI_SPI_CMD_BUFFER,
  MpiTargetScsiSpiCmdBuffer, MPI_POINTER pMpiTargetScsiSpiCmdBuffer;


/****************************************************************************/
/* Target Assist Request                                                    */
/****************************************************************************/

typedef struct _MSG_TARGET_ASSIST_REQUEST
{
    U8                      StatusCode;
    U8                      TargetAssistFlags;
    U8                      ChainOffset;
    U8                      Function;
    U16                     QueueTag;
    U8                      Reserved;
    U8                      MsgFlags;
    U32                     MsgContext;
    U32                     ReplyWord;
    U8                      LUN[8];
    U32                     RelativeOffset;
    U32                     DataLength;
    SGE_IO_UNION            SGL[1];
} MSG_TARGET_ASSIST_REQUEST, MPI_POINTER PTR_MSG_TARGET_ASSIST_REQUEST,
  TargetAssistRequest_t, MPI_POINTER pTargetAssistRequest_t;

#define TARGET_ASSIST_FLAGS_DATA_DIRECTION          (0x01)
#define TARGET_ASSIST_FLAGS_AUTO_STATUS             (0x02)
#define TARGET_ASSIST_FLAGS_HIGH_PRIORITY           (0x04)
#define TARGET_ASSIST_FLAGS_REPOST_CMD_BUFFER       (0x80)


typedef struct _MSG_TARGET_ERROR_REPLY
{
    U16                     Reserved;
    U8                      MsgLength;
    U8                      Function;
    U16                     Reserved1;
    U8                      Reserved2;
    U8                      MsgFlags;
    U32                     MsgContext;
    U16                     Reserved3;
    U16                     IOCStatus;
    U32                     IOCLogInfo;
    U32                     ReplyWord;
    U32                     TransferCount;
} MSG_TARGET_ERROR_REPLY, MPI_POINTER PTR_MSG_TARGET_ERROR_REPLY,
  TargetErrorReply_t, MPI_POINTER pTargetErrorReply_t;


/****************************************************************************/
/* Target Status Send Request                                               */
/****************************************************************************/

typedef struct _MSG_TARGET_STATUS_SEND_REQUEST
{
    U8                      StatusCode;
    U8                      StatusFlags;
    U8                      ChainOffset;
    U8                      Function;
    U16                     QueueTag;
    U8                      Reserved;
    U8                      MsgFlags;
    U32                     MsgContext;
    U32                     ReplyWord;
    U8                      LUN[8];
    SGE_SIMPLE_UNION        StatusDataSGE;
} MSG_TARGET_STATUS_SEND_REQUEST, MPI_POINTER PTR_MSG_TARGET_STATUS_SEND_REQUEST,
  TargetStatusSendRequest_t, MPI_POINTER pTargetStatusSendRequest_t;

#define TARGET_STATUS_SEND_FLAGS_AUTO_GOOD_STATUS   (0x01)
#define TARGET_STATUS_SEND_FLAGS_REPOST_CMD_BUFFER  (0x80)


/****************************************************************************/
/* Target Mode Abort Request                                                */
/****************************************************************************/

typedef struct _MSG_TARGET_MODE_ABORT_REQUEST
{
    U8                      AbortType;
    U8                      Reserved;
    U8                      ChainOffset;
    U8                      Function;
    U16                     Reserved1;
    U8                      Reserved2;
    U8                      MsgFlags;
    U32                     MsgContext;
    U32                     ReplyWord;
    U32                     MsgContextToAbort;
} MSG_TARGET_MODE_ABORT, MPI_POINTER PTR_MSG_TARGET_MODE_ABORT,
  TargetModeAbort_t, MPI_POINTER pTargetModeAbort_t;

#define TARGET_MODE_ABORT_TYPE_ALL_CMD_BUFFERS      (0x00)
#define TARGET_MODE_ABORT_TYPE_ALL_IO               (0x01)
#define TARGET_MODE_ABORT_TYPE_EXACT_IO             (0x02)
#define TARGET_MODE_ABORT_TYPE_EXACT_IO_REQUEST     (0x03)

/* Target Mode Abort Reply */

typedef struct _MSG_TARGET_MODE_ABORT_REPLY
{
    U16                     Reserved;
    U8                      MsgLength;
    U8                      Function;
    U16                     Reserved1;
    U8                      Reserved2;
    U8                      MsgFlags;
    U32                     MsgContext;
    U16                     Reserved3;
    U16                     IOCStatus;
    U32                     IOCLogInfo;
    U32                     AbortCount;
} MSG_TARGET_MODE_ABORT_REPLY, MPI_POINTER PTR_MSG_TARGET_MODE_ABORT_REPLY,
  TargetModeAbortReply_t, MPI_POINTER pTargetModeAbortReply_t;


/****************************************************************************/
/* Target Mode Context Reply                                                */
/****************************************************************************/

#define TARGET_MODE_REPLY_IO_INDEX_MASK         (0x00003FFF)
#define TARGET_MODE_REPLY_IO_INDEX_SHIFT        (0)
#define TARGET_MODE_REPLY_INITIATOR_INDEX_MASK  (0x03FFC000)
#define TARGET_MODE_REPLY_INITIATOR_INDEX_SHIFT (14)
#define TARGET_MODE_REPLY_ALIAS_MASK            (0x0C000000)
#define TARGET_MODE_REPLY_ALIAS_SHIFT           (26)
#define TARGET_MODE_REPLY_PORT_MASK             (0x10000000)
#define TARGET_MODE_REPLY_PORT_SHIFT            (28)


#define GET_IO_INDEX(x)     (((x) & TARGET_MODE_REPLY_IO_INDEX_MASK)           \
                                    >> TARGET_MODE_REPLY_IO_INDEX_SHIFT)

#define SET_IO_INDEX(t, i)                                                     \
            ((t) = ((t) & ~TARGET_MODE_REPLY_IO_INDEX_MASK) |                  \
                              (((i) << TARGET_MODE_REPLY_IO_INDEX_SHIFT) &     \
                                             TARGET_MODE_REPLY_IO_INDEX_MASK))

#define GET_INITIATOR_INDEX(x) (((x) & TARGET_MODE_REPLY_INITIATOR_INDEX_MASK) \
                                   >> TARGET_MODE_REPLY_INITIATOR_INDEX_SHIFT)

#define SET_INITIATOR_INDEX(t, ii)                                             \
        ((t) = ((t) & ~TARGET_MODE_REPLY_INITIATOR_INDEX_MASK) |               \
                        (((ii) << TARGET_MODE_REPLY_INITIATOR_INDEX_SHIFT) &   \
                                      TARGET_MODE_REPLY_INITIATOR_INDEX_MASK))

#define GET_ALIAS(x) (((x) & TARGET_MODE_REPLY_ALIAS_MASK)                     \
                                               >> TARGET_MODE_REPLY_ALIAS_SHIFT)

#define SET_ALIAS(t, a)  ((t) = ((t) & ~TARGET_MODE_REPLY_ALIAS_MASK) |        \
                                    (((a) << TARGET_MODE_REPLY_ALIAS_SHIFT) &  \
                                                 TARGET_MODE_REPLY_ALIAS_MASK))

#define GET_PORT(x) (((x) & TARGET_MODE_REPLY_PORT_MASK)                       \
                                               >> TARGET_MODE_REPLY_PORT_SHIFT)

#define SET_PORT(t, p)  ((t) = ((t) & ~TARGET_MODE_REPLY_PORT_MASK) |          \
                                    (((p) << TARGET_MODE_REPLY_PORT_SHIFT) &   \
                                                  TARGET_MODE_REPLY_PORT_MASK))


#endif

