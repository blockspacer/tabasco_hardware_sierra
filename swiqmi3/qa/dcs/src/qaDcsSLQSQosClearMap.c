/*
 * \ingroup dcs
 *
 * \file    qaDcsSLQSQosClearMap
 *
 * \brief   Contains Packing and UnPacking routines for the
 *          eQMI_DCS_QOS_CLEAR_MAP message.
 *
 * Copyright: © 2013 Sierra Wireless, Inc. all rights reserved
 *
 */
/* include files */

#include "SwiDataTypes.h"
#include "qaQmiBasic.h"
#include "sludefs.h"
#include "qmudefs.h"
#include "qmerrno.h"

#include "qaDcsSLQSQosClearMap.h"
#include "qaGobiApiDcs.h"

/******************************************************************************
 * Request handling
 ******************************************************************************/
/*
 * This function packs the SLQSQosClearMap parameters
 * to the QMI message SDU
 *
 * \param   pParamField [OUT] - Pointer to storage into which the packed
 *                              data will be placed by this function.
 *
 * \param   pMlength    [OUT] - Total length of built message.
 *
 * \return  eQCWWAN_ERR_NONE
 * \return  eQCWWAN_ERR_MEMORY
 *
 * \sa      qaGobiApiDcs.h for remaining parameter descriptions.
 *
 */
enum eQCWWANError PkQmiDcsSLQSQosClearMap(
    WORD *pMlength,
    BYTE *pParamField)
{
    return qm_dcs_qos_clear_map_pack( pParamField, pMlength );
}

/******************************************************************************
 * Response handling
 ******************************************************************************/
/*
 * This function unpacks the SLQSQosClearMap response message to a
 * user-provided response structure.
 *
 * \param     pMdmResp   [IN]  - Pointer to packed response from the modem.
 *
 * \param     pApiResp   [OUT] - Pointer to storage to unpack into.
 *
 * \return  eQCWWAN_ERR_NONE
 * \return  eQCWWAN_ERR_MEMORY
 */
enum eQCWWANError  UpkQmiDcsSLQSQosClearMap(
    BYTE *pMdmResp,
    struct qm_qmi_response_tlvs_values *pApiResp)
{
    return qm_dcs_qos_clear_map_response_unpack( pMdmResp, pApiResp );
}

