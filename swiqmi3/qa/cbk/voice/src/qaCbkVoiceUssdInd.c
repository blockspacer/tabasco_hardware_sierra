/*
 * \ingroup cbk
 *
 * \file    qaCbkVoiceUssdInd.c
 *
 * \brief   Contains UnPacking routines for the QMI_VOICE_USSD_IND message.
 *
 * Copyright: © 2011 Sierra Wireless, Inc. all rights reserved
 *
 */

/* include files */

#include "SwiDataTypes.h"
#include "qmudefs.h"
#include "qmerrno.h"
#include "qaCbkVoiceUssdInd.h"
#include "qaGobiApiCbk.h"          /* for USSD coding scheme*/

/* function prototypes */
extern swi_bool slUcs2ToUtf8(
    swi_UCS2   *ucs2stringp,
    swi_uint16 numucs2chars,
    unsigned char *utf8stringp,
    swi_uint16 maxbytes);

/* Functions */

/*
 * This function unpacks the USSDNotificationType TLV parameters from the QMI
 * indication message to a user provided response structure
 *
 * \param   pTlvData - Pointer to TLV data from which to unpack.
 *
 * \param   pResp    - Pointer to structure containing storage
 *                     to return data for this TLV.
 *
 * \return: eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 */
package enum eQCWWANError UnpackCbkTlvUSSDNotificationType(
    BYTE *pTlvData,
    BYTE *pResp )
{
    /* Get the required TLV structure to the local pointer */
    struct VoiceUssdTlv *lResponse =
        &((struct QmiCbkVoiceUssdInd *)pResp)->VSTlv;

    BYTE lByte = 0;
    enum eQCWWANError eRCode = eQCWWAN_ERR_NONE;

    /* Extract the Notification Type*/
    eRCode = GetByte( pTlvData, &lByte);
    if( eQCWWAN_ERR_NONE == eRCode )
    {
        lResponse->Notification_Type = lByte;

        /* Initilize the remaining structure elements */
        lResponse->TlvPresent  = TRUE;
        return eRCode;
    }

    return eRCode;
}

/*
 * This function unpacks the UssdDataNetwork TLV from the QMI indication
 * message to a user provided response structure
 *
 * \param   pTlvData - Pointer to TLV data from which to unpack.
 *
 * \param   pResp    - Pointer to structure containing storage
 *                     to return data for this TLV.
 *
 * \return: eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 */
package enum eQCWWANError UnpackCbkTlvUssdDataNetwork(
    BYTE *pTlvData,
    BYTE *pResp )
{
    BYTE              uCount = 0;
    enum eQCWWANError eRCode = eQCWWAN_ERR_NONE;

    /* Get the required TLV structure to the local pointer */
    struct USSInfo *lResponse =
        &((struct QmiCbkVoiceUssdInd *)pResp)->VSTlv.NetworkInfo;

    struct VoiceUssdTlv *lResp =
        &((struct QmiCbkVoiceUssdInd *)pResp)->VSTlv;

    /* Extract the ussDCS*/
    eRCode = GetByte( pTlvData, &(lResponse->ussDCS) );
    if( eRCode != eQCWWAN_ERR_NONE )
        return eRCode;

    /* Extract the ussLen*/
    eRCode = GetByte( pTlvData, &(lResponse->ussLen) );
    if ( eRCode != eQCWWAN_ERR_NONE )
        return eRCode;

    /* Check if DCS is ucs2 coding scheme */
    if( USSD_DCS_UCS2 == lResponse->ussDCS )
    {
        BYTE ussData[MAXUSSDLENGTH];

        /* Extract the Data encoded as UCS2*/
        while ((uCount < lResponse->ussLen) && (eRCode == eQCWWAN_ERR_NONE))
        {
            eRCode = GetByte( pTlvData, &ussData[uCount+1] );
            eRCode = GetByte( pTlvData, &ussData[uCount] );
            uCount+=2;
        }
        /* convert ucs2 to utf-8 for Android*/
        slUcs2ToUtf8( (swi_UCS2 *)ussData, uCount/2, (unsigned char *)&lResponse->ussData, MAXUSSDLENGTH);
    }
    else /* ASCII coding scheme */
    {
    	/* Extract the Data encoded as ASCII*/
        while ((uCount < lResponse->ussLen) && (eRCode == eQCWWAN_ERR_NONE))
        {
            eRCode = GetByte( pTlvData, &lResponse->ussData[uCount] );
            uCount++;
        }
    }

    /* Initilize the remaining structure elements */
    lResp->TlvPresent  = TRUE;
    return eRCode;
}

/*
 * This function unpacks the Event Report Indication message to a
 * user-provided response structure.
 *
 * \param   pMdmResp - Pointer to packed response from the modem.
 *
 * \param   pApiResp - Pointer to storage to unpack into.
 *
 * \return: eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 */
package enum eQCWWANError UpkQmiCbkVoiceUssdInd(
    BYTE                      *pMdmResp,
    struct QmiCbkVoiceUssdInd *pApiResp )
{
    enum eQCWWANError eRCode;

    static struct qmTlvUnpackerItem map[] =
    {
        { eTLV_USSD_NOTIFICATION_TYPE, &UnpackCbkTlvUSSDNotificationType},
        { eTLV_USSD_DATA_NETWORK,      &UnpackCbkTlvUssdDataNetwork },
        { eTLV_TYPE_INVALID,           NULL } /* Important. Sentinel.
                                               * Signifies last item in map.
                                               */
    };

    eRCode = qmunpackresp( pMdmResp,
                           (BYTE *)pApiResp,
                           map,
                           eQMI_VOICE_USSD_IND );
    return eRCode;
}
