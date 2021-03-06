/*
 * \ingroup fms
 *
 * \file    qaFmsSetImagePath.h
 *
 * \brief   This file contains definitions, enumerations, structures and
 *          forward declarations for qaFmsSetImagePath.c
 *
 * Copyright: © 2011 Sierra Wireless, Inc. all rights reserved
 *
 */
#ifndef __FMS_SETIMAGEPATH_H__
#define __FMS_SETIMAGEPATH_H__

/* Prototypes */
ULONG SetImagePath(
    CHAR    *path,
    ULONG   isMDM9x15,
    WORD    imgMask,
    BYTE    mdmProtocol );

enum eQCWWANError PkQmiFmsSetImagePath(
    WORD    *pMlength,
    BYTE    *pParamField,
    CHAR    *path,
    ULONG   isMDM9x15,
    WORD    imgMask,
    WORD    mdmProtocol );

enum eQCWWANError UpkQmiFmsSetImagePath(
    BYTE   *pMdmResp,
    struct qm_qmi_response_tlvs_values *pApiResp );

#endif /* __FMS_SETIMAGEPATH_H__ */
