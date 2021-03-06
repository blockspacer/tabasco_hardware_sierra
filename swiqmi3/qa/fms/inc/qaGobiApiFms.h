/**
 * \ingroup fms
 *
 * \file    qaGobiApiFms.h
 *
 * \brief   Firmware Management Service API function prototypes
 */

/*
 * Copyright: © 2011-2105 Sierra Wireless, Inc. all rights reserved
 */
#ifndef __GOBI_API_FMS_H__
#define __GOBI_API_FMS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* MC7xx CWE Header SPKGS defines */
#define SLQSFWINFO_MODELID_SZ     20
#define SLQSFWINFO_BOOTVERSION_SZ 85
#define SLQSFWINFO_APPVERSION_SZ  85
#define SLQSFWINFO_SKU_SZ         15
#define SLQSFWINFO_PACKAGEID_SZ   85
#define SLQSFWINFO_CARRIER_SZ     20
#define SLQSFWINFO_PRIVERSION_SZ  10
/* Gobi .mbn image defines */
#define GOBI_MBN_IMG_ID_STR_LEN   16
#define GOBI_MBN_BUILD_ID_STR_LEN 100
#define GOBI_LISTENTRIES_MAX      2
#define GOBI_SET_IMG_PREF_RSPLEN  40
#define DEVICE_SHUTDOWN           5
#define DEVICE_RESET              4
#define FIRMWARE_UPDATE_SUCCESS   0x01
#define FIRMWARE_UPDATE_FAIL      0x01
#define PRI_UPDATE_FAIL           0x02
#define FIRMWARE_UPGRADE_SUCCESS  0x00

/**
 * Gobi firmware image info structure
 *
 * \param   FirmwareID
 *          - Firmware ID obtained from the firmware image
 * \param   Technology
 *          - Technology (0xFFFFFFFF if unknown)
 * \param   Carrier
 *          - Carrier (0xFFFFFFFF if unknown)
 * \param   Region
 *          - Region (0xFFFFFFFF if unknown)
 * \param   GPSCapability
 *          - GPS capability (0xFFFFFFFF if unknown)
 */
struct fwinfo_s
{
    ULONG FirmwareID;
    ULONG Technology;
    ULONG Carrier;
    ULONG Region;
    ULONG GPSCapability;
};

/**
 * SPKG CWE firmware image info structure
 *
 * \param   modelid_str
 *          - device model identifier string
 * \param   bootversion_str
 *          - firmware boot version string
 * \param   appversion_str
 *          - firmware application version string
 * \param   sku_str
 *          - SKU(PRI) string
 * \param   packageid_str
 *          - package identifier string
 * \param   carrier_str
 *          - carrier string
 *          - See qaGobiApiTableCarrierCodes.h for carrier codes
 * \param   priversion_str
 *          - PRI version string
 */
struct slqsfwinfo_s{
    CHAR modelid_str[SLQSFWINFO_MODELID_SZ];
    CHAR bootversion_str[SLQSFWINFO_BOOTVERSION_SZ];
    CHAR appversion_str[SLQSFWINFO_APPVERSION_SZ];
    CHAR sku_str[SLQSFWINFO_SKU_SZ];
    CHAR packageid_str[SLQSFWINFO_PACKAGEID_SZ];
    CHAR carrier_str[SLQSFWINFO_CARRIER_SZ];
    CHAR priversion_str[SLQSFWINFO_PRIVERSION_SZ];
};

/**
 * Top level structure for storing information about firmware images.
 * union of structures depending on device type, MC77xx or MC83xx
 * \param   g - structure for MC83xx devices
 * \param   s - structure for devices with SPKG CWE file support
 *
 * - List of various Firmware Images Supported
 *
  \verbatim
  Technology  Initials  Carrier                      Region                Network Technology
  ----------  --------  ---------------------------  -------------------  --------------------
  D3600       S         eGOBI_IMG_CAR_SPRINT         eGOBI_IMG_REG_NA      eGOBI_IMG_TECH_CDMA
  D3600       V         eGOBI_IMG_CAR_VERIZON        eGOBI_IMG_REG_NA      eGOBI_IMG_TECH_CDMA
  D3600       C         eGOBI_IMG_CAR_CHINA_TELECOM  eGOBI_IMG_REG_ASIA    eGOBI_IMG_TECH_CDMA
  D3600       G         eGOBI_IMG_CAR_GENERIC_CDMA   eGOBI_IMG_REG_GLOBAL  eGOBI_IMG_TECH_CDMA (item for Generic CDMA UQCN)
  D3600       H         eGOBI_IMG_CAR_GENERIC_CDMA   eGOBI_IMG_REG_GLOBAL  eGOBI_IMG_TECH_CDMA (item for Generic CDMA AMSS)
  D3200       V         eGOBI_IMG_CAR_VODAFONE       eGOBI_IMG_REG_NA      eGOBI_IMG_TECH_UMTS
  D3200       A         eGOBI_IMG_CAR_ATT            eGOBI_IMG_REG_NA      eGOBI_IMG_TECH_UMTS
  D3200       L         eGOBI_IMG_CAR_TMOBILE        eGOBI_IMG_REG_EU      eGOBI_IMG_TECH_UMTS
  D3200       G         eGOBI_IMG_CAR_GENERIC        eGOBI_IMG_REG_GLOBAL  eGOBI_IMG_TECH_UMTS
  D3200       H         eGOBI_IMG_CAR_TELEFONICA     eGOBI_IMG_REG_EU      eGOBI_IMG_TECH_UMTS
  D3200       I         eGOBI_IMG_CAR_TELCOM_ITALIA  eGOBI_IMG_REG_NA      eGOBI_IMG_TECH_UMTS
  D3200       O         eGOBI_IMG_CAR_ORANGE         eGOBI_IMG_REG_NA      eGOBI_IMG_TECH_UMTS
  D3200       U         eGOBI_IMG_CAR_GENERIC        eGOBI_IMG_REG_GLOBAL  eGOBI_IMG_TECH_UMTS
  D3200       R         eGOBI_IMG_CAR_ROGERS         eGOBI_IMG_REG_NA      eGOBI_IMG_TECH_UMTS
  D3600       A         eGOBI_IMG_CAR_AERIS          eGOBI_IMG_REG_NA      eGOBI_IMG_TECH_CDMA
  \endverbatim
 *
 * \sa      fwinfo_s
 * \sa      slqsfwinfo_s
 */
struct qmifwinfo_s
{
    union
    {
        struct fwinfo_s     g;
        struct slqsfwinfo_s s;
    } dev;
};

/**
 *  Returns the image store folder, i.e., the folder containing one or more
 *  carrier-specific image subfolders compatible with the currently connected
 *  QC WWAN device.
 *
 *  \param  imageStorePathSize
 *          - Maximum number of characters (including NULL terminator) that can
 *            be copied to the image store path array.
 *
 *  \param  pImageStorePath[OUT]
 *          - The path to the image store
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
extern ULONG GetImageStore(
    WORD imageStorePathSize,
    CHAR *pImageStorePath );

/**
 * enumeration which lists the technology supported by the image
 */
enum eGobiImageTech
{
   eGOBI_IMG_TECH_CDMA = 0,      /* 0 - CDMA */
   eGOBI_IMG_TECH_UMTS           /* 1 - UMTS */
};

/**
 * enumeration which lists the carrier supported by the image
 */
enum eGobiImageCarrier
{
   eGOBI_IMG_CAR_GENERIC = 1,    /* 001 */
   eGOBI_IMG_CAR_FACTORY,        /* 002 */
   eGOBI_IMG_CAR_NORF,           /* 003 */

   eGOBI_IMG_CAR_VERIZON = 101,  /* 101 */
   eGOBI_IMG_CAR_SPRINT,         /* 102 */
   eGOBI_IMG_CAR_ALLTEL,         /* 103 */
   eGOBI_IMG_CAR_BELL,           /* 104 */
   eGOBI_IMG_CAR_TELUS,          /* 105 */
   eGOBI_IMG_CAR_US,             /* 106 */
   eGOBI_IMG_CAR_TELSTRA1,       /* 107 */
   eGOBI_IMG_CAR_CHINA_UNICOM,   /* 108 */
   eGOBI_IMG_CAR_TELCOM_NZ,      /* 109 */
   eGOBI_IMG_CAR_SK_TELCOM1,     /* 110 */
   eGOBI_IMG_CAR_RELIANCE1,      /* 111 */
   eGOBI_IMG_CAR_TATA,           /* 112 */
   eGOBI_IMG_CAR_METROPCS,       /* 113 */
   eGOBI_IMG_CAR_LEAP,           /* 114 */
   eGOBI_IMG_CAR_KDDI,           /* 115 */
   eGOBI_IMG_CAR_IUSACELL,       /* 116 */
   eGOBI_IMG_CAR_CHINA_TELECOM,  /* 117 */
   eGOBI_IMG_CAR_OMH,            /* 118 */
   eGOBI_IMG_CAR_GENERIC_CDMA,   /* 119 */

   eGOBI_IMG_CAR_ATT = 201,      /* 201 */
   eGOBI_IMG_CAR_VODAFONE,       /* 202 */
   eGOBI_IMG_CAR_TMOBILE,        /* 203 */
   eGOBI_IMG_CAR_ORANGE,         /* 204 */
   eGOBI_IMG_CAR_TELEFONICA,     /* 205 */
   eGOBI_IMG_CAR_TELCOM_ITALIA,  /* 206 */
   eGOBI_IMG_CAR_3,              /* 207 */
   eGOBI_IMG_CAR_O2,             /* 208 */
   eGOBI_IMG_CAR_SFR,            /* 209 */
   eGOBI_IMG_CAR_SWISSCOM,       /* 210 */
   eGOBI_IMG_CAR_CHINA_MOBILE,   /* 211 */
   eGOBI_IMG_CAR_TELSTRA2,       /* 212 */
   eGOBI_IMG_CAR_SINGTEL_OPTUS,  /* 213 */
   eGOBI_IMG_CAR_RELIANCE2,      /* 214 */
   eGOBI_IMG_CAR_BHARTI,         /* 215 */
   eGOBI_IMG_CAR_NTT_DOCOMO,     /* 216 */
   eGOBI_IMG_CAR_EMOBILE,        /* 217 */
   eGOBI_IMG_CAR_SOFTBANK,       /* 218 */
   eGOBI_IMG_CAR_KT_FREETEL,     /* 219 */
   eGOBI_IMG_CAR_SK_TELCOM2,     /* 220 */
   eGOBI_IMG_CAR_TELENOR,        /* 221 */
   eGOBI_IMG_CAR_NETCOM,         /* 222 */
   eGOBI_IMG_CAR_TELIASONERA,    /* 223 */
   eGOBI_IMG_CAR_AMX_TELCEL,     /* 224 */
   eGOBI_IMG_CAR_BRASIL_VIVO,    /* 225 */
   eGOBI_IMG_CAR_AERIS,          /* 226 */
   eGOBI_IMG_CAR_ROGERS          /* 227 */
};

/**
 * enumeration which lists the region supported by the image
 */
enum eGobiImageRegion
{
   eGOBI_IMG_REG_NA = 0,         /* 0 - North America */
   eGOBI_IMG_REG_LA,             /* 1 - Latin America */
   eGOBI_IMG_REG_EU,             /* 2 - Europe */
   eGOBI_IMG_REG_ASIA,           /* 3 - Asia */
   eGOBI_IMG_REG_AUS,            /* 4 - Australia */
   eGOBI_IMG_REG_GLOBAL          /* 5 - Global */
};

/**
 * enumeration which lists the GPS type supported by the image
 */
enum eGobiImageGPS
{
   eGOBI_IMG_GPS_NONE = 0,       /* 0 - None */
   eGOBI_IMG_GPS_STAND_ALONE,    /* 1 - Stand-alone */
   eGOBI_IMG_GPS_ASSISTED,       /* 2 - Stand-alone + AGPS + XTRA */
   eGOBI_IMG_GPS_NO_XTRA         /* 3 - Stand-alone + AGPS */
};

/**
 *  Returns firmware image information from the connected device
 *
 *  \param  pinfo[OUT]
 *          - firmware image information record
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *  \sa     struct qmifwinfo_s
 *
 *  \note   Timeout: 2 Seconds.
 *
 */
ULONG SLQSGetFirmwareInfo(
    struct qmifwinfo_s *pinfo );

/**
 *  Returns firmware image information from a SPKGS CWE file stored on the host.
 *  The information is returned for the first SPKGS CWE image found at the
 *  specified path. This API executes independent of a MC77xx being connected
 *  to the target.
 *
 *  \param  path[IN]
 *          - fully qualified path to folder containing SPKG CWE image
 *          - should use a "/" at the end of the path.
 *
 *  \param  pinfo[OUT]
 *          - firmware image information record
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *  \sa     struct qmifwinfo_s
 *
 *  \note   Device Supported: MC77xx\n
 *          Timeout: N/A\n
 *
 */
ULONG SLQSGetImageInfoMC77xx(
    LPCSTR              path,
    struct qmifwinfo_s *pinfo );

/**
 *  Returns firmware image information from an MBN file located on the host.
 *  This API executes independent of a MC83xx being connected to the target.
 *
 *  \param  path[IN]
 *          - fully qualified path to folder containing MBN file
 *          - should use a "/" at the end of the path.
 *
 *  \param  pinfo[OUT]
 *          - firmware image information record
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *  \sa     struct qmifwinfo_s
 *
 *  \note   Device Supported: MC83xx/SL9090\n
 *          Timeout: N/A\n
 *
 */
ULONG SLQSGetImageInfoMC83xx(
    LPCSTR              path,
    struct qmifwinfo_s *pinfo );

/**
 *  Returns firmware image information from a CWE file  or mbn files stored
 *  on the host. For CWE, information is returned for the first CWE image found
 *  at the specified path. For MBN, the provided path must be located under the
 *  image store for the currently connected QC WWAN device. Note that as this
 *  API supports multiple firmware image types, it relies on the presence of a
 *  supported device. Otherwise, refer to SLQSGetImageInfoMC83xx and
 *  SLQSGetImageInfoMC77xx for APIs which do not rely on the presence of a
 *  supported device.
 *
 *  \param  path[IN]
 *          - fully qualified path to folder containing CWE image or MBN images
 *          - should use a "/" at the end of the path.
 *
 *  \param  pinfo[OUT]
 *          - firmware image information record
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *  \sa     struct qmifwinfo_s
 *
 *  \note   Timeout: N/A\n
 *
 */
ULONG SLQSGetImageInfo(
    LPCSTR path,
    struct qmifwinfo_s *pinfo );

/**
 *  This API is used to download firmware to a MC77xx or Gobi 3000 device.
 *
 *  This API Performs the following steps:\n
 *  1. Verifies arguments.\n
 *  2. Informs the SDK of the firmware upgrade path\n
 *  3. Updates the images preference on the currently connected device.\n
 *  4. Requests the device reset (device will reset after all open handles are
 *     released).\n
 *
 *  Upon successful completion, the above steps will have been completed,
 *  however, the actual upgrade of the firmware will necessarily then follow.
 *
 *  \param  pDestinationPath[IN]
 *          - fully qualified path to firmware image to download. The path must\n
 *            end with a forward slash. For a Gobi 3000 device the path should\n
 *            specify the carrier image folder index i.e.\n
 *            "<path\to\carrier\image>/<carrier index>/" where <carrier index>\n
 *            is a valid sub-directory entry. For 9x30 devices if pDestinationPath\n
 *            is not valid on host, it will use pseudo path for image switching.
 *
 * \param   bForceDownload[IN]
 *          - forcefully download same or old version of firmware
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   Timeout: 12 seconds\n
 *
 */
ULONG UpgradeFirmware2k(
    CHAR *pDestinationPath,
    ULONG bForceDownload
   );

/**
 *  This API is used to download firmware to a Gobi 3000 device.
 *
 *  This API Performs the following steps:\n
 *  1. Verifies arguments.\n
 *  2. Informs the SDK of the firmware upgrade path\n
 *  3. Updates the images preference on the currently connected device.\n
 *  4. Requests the device reset (device will reset after all open handles are
 *     released).\n
 *
 *  Upon successful completion, the above steps will have been completed,
 *  however, the actual upgrade of the firmware will necessarily then follow.
 *
 *  \param  pDestinationPath[IN]
 *          - fully qualified path to firmware image to download. The path must\n
 *            end with a forward slash. For a Gobi 3000 device the path should\n
 *            specify the carrier image folder index i.e.\n
 *            "<path\to\carrier\image>/<carrier index>/" where <carrier index>\n
 *            is a valid sub-directory entry
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   Timeout: 12 seconds\n
 *
 */
ULONG UpgradeFirmwareG3k(
    CHAR *pDestinationPath );

/**
 * push current alignment to stack
 * set alignment to 1 byte boundary
 */
#pragma pack(push)
#pragma pack(1)

/**
 * This structure contains the Image Element information
 *
 *  \param  imageType
 *              - Type of image
 *                 0 - Modem
 *                 1 - PRI
 *
 *  \param  imageId
 *              - Unique image identifier
 *
 *  \param  buildIdLength
 *              - Length of the build ID string (may be zero)
 *
 *  \param  pBuildId
 *              - Build ID ANSI string with length provided
 *              by the previous field
 *
 */
struct ImageElement
{
    BYTE imageType;
    BYTE imageId[GOBI_MBN_IMG_ID_STR_LEN];
    BYTE buildIdLength;
    CHAR buildId[GOBI_MBN_BUILD_ID_STR_LEN];
};

/**
 * This structure contains the Preference Image List information
 *
 *  \param  listSize
 *              - The number of elements in the image list
 *
 *  \param  pListEntries
 *              - Array of Image entries with size provided by
 *                previous field
 *              - See \ref ImageElement
 *
 */
struct PrefImageList
{
    BYTE                listSize;
    struct ImageElement listEntries[GOBI_LISTENTRIES_MAX];
};

/**
 * restore original alignment from stack
 */
#pragma pack(pop)

/**
 *  Gets the current images preference from the device.
 *
 *  \param  pImageListSize[IN/OUT]
 *          - Upon input, the size of structure ImageList \ref ImageList
 *          - Upon successful output, the number of BYTEs copied to the image
 *            list array\n
 *
 *  \param  pImageList[OUT]
 *          - The caller must supply a pointer to a \ref ImageList structure
 *            typecast as a BYTE pointer
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   Timeout: 2 seconds
 *
 */

extern ULONG GetImagesPreference(
    ULONG *pImageListSize,
    BYTE  *pImageList );

/**
 *  Sets the current images preference on the device.
 *  After this function successfully  completes, the device must be reset
 *  for the selected image preference to be realized. Additionally, when
 *  the returned list of image types that require downloading is not empty,
 *  the device opens in  QDL mode after the reset. At that point, the QDL
 *  portion of this API must be used to download  the selected image preference
 *  to the device.
 *
 *  \param  imageListSize
 *          - The size in BYTEs of the image list array
 *
 *  \param  pImageList[IN]
 *          - The image info list array containing Image Elements
 *              - See \ref PrefImageList
 *
 *  \param  bForceDownload[IN]
 *          - Force device to download images from host?
 *                0       - No
 *                Nonzero - Yes
 *
 *  \param  modemIndex
 *          - Desired storage index for downloaded modem image
 *            (optional, a value of 0xFF indicates unspecified)
 *
 * \param  pImageTypesSize[IN/OUT]
 *          - Upon input, maximum number of elements that download image
 *            types array can contain
 *          - Upon successful output, number of elements in download image
 *            types array

 * \param  pImageTypes[OUT]
 *          -The download image types array.
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   Timeout: 2 seconds
 *
 */
extern ULONG SetImagesPreference(
    ULONG imageListSize,
    BYTE  *pImageList,
    ULONG bForceDownload,
    BYTE  modemIndex,
    ULONG *pImageTypesSize,
    BYTE  *pImageTypes );

/**
 * push current alignment to stack
 * set alignment to 1 byte boundary
 */
#pragma pack(push)
#pragma pack(1)

/**
 * This structure contains the Image ID list element Information
 *
 *  \param  storageIndex
 *          - Index in storage where the image is located(a value of 0xFF
 *            indicates that the storage for this type of image is not relevant)
 *
 *  \param  failureCount
 *          - Number of consecutive write attempts to this storage index
 *            that have failed(a value of 0xFF indicates unspecified)
 *
 *  \param  imageID
 *          - Image unique identifier(max 16 chars.)
 *
 *  \param  buildIDLength
 *          - Length of the build ID string. If there is no build ID, this
 *            field will be 0 and no data will follow.
 *
 *  \param  buildID
 *          - String containing image build information( Max 100 characters )
 */
struct ImageIdElement
{
    BYTE storageIndex;
    BYTE failureCount;
    BYTE imageID[16];
    BYTE buildIDLength;
    CHAR buildID[GOBI_MBN_BUILD_ID_STR_LEN];
};

/**
 * This structure contains the list entry Information
 *
 *  \param  imageType
 *          - Type of image
 *              - 0 - Modem
 *              - 1 - PRI
 *
 *  \param  maxImages
 *          - Maximum number of images of this type that may be stored
 *            concurrently on the device
 *
 *  \param  executingImage
 *          - Index (into the next array) of image that is currently executing
 *
 *  \param  imageIDSize
 *          - The number of elements in the image ID list
 *
 *  \param  imageIDElement
 *          - Array of ImageIDElement Structure ( Max 50 elements )
 */
struct ImageIDEntries
{
    BYTE                  imageType;
    BYTE                  maxImages;
    BYTE                  executingImage;
    BYTE                  imageIDSize;
    struct ImageIdElement imageIDElement[50];
};

/**
 * This structure contains the Get Stored Images List
 *
 *  \param  listSize
 *          - The number of elements in the image list
 *
 *  \param  imageIDEntries
 *          - Array of ImageIDEntries Structure ( Max 2 entries )
 */
struct ImageList
{
    BYTE                  listSize;
    struct ImageIDEntries imageIDEntries[2];
};

/**
 * restore original alignment from stack
 */
#pragma pack(pop)

/**
 *  Gets the list of images stored on the device.
 *
 *  \param  pImageListSize[IN/OUT]
 *          - Upon input, the size of structure ImageList \ref ImageList
 *          - Upon successful output, the number of BYTEs copied to the image
 *            list array\n
 *
 *  \param  pImageList[OUT]
 *          - The caller must supply a pointer to a \ref ImageList structure
 *            typecast as a BYTE pointer
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   Device Supported: MC83x5/SL9090\n
 *          Timeout: 2 seconds
 *
 */
ULONG GetStoredImages(
    ULONG *pImageListSize,
    BYTE  *pImageList );

/**
 *  Used to delete the specified image from the device.
 *  This API function is only relevant to devices with the ability to store
 *  multiple firmware images(see Device Supported section below).
 *
 *  \param  imageInfoSize[IN]
 *          - The size in BYTEs of the image info array
 *
 *  \param  pImageInfo[IN]
 *          - The image info list array containing information about the image
 *            to be deleted.
 *          - See \ref ImageElement
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   Device Supported: MC83x5/SL9090\n
 *          Timeout: 2 Secs
 *
 */
ULONG DeleteStoredImage(
    ULONG imageInfoSize,
    BYTE  *pImageInfo );


/*
 *  Name    : IsGobiDevice
 *  Purpose : To Check device description
 */
BOOL IsGobiDevice(void);


/**
 *  Name    : IsSierraGobiDevice
 *  Purpose : To Check device description
 */
BOOL IsSierraGobiDevice(void);

/**
 *  Returns firmware image information from a CWE file(s) stored
 *  on the host. It does not rely on the presence of a
 *  supported device.
 *
 *  \param  path[IN]
 *          - fully qualified path to folder containing the image(s)
 *          - should use a "/" at the end of the path.
 *
 *  \param  imgType[IN]
 *          - 2 - Firmware Image( .cwe extension )
 *          - 3 - PRI Image ( .nvu extension )
 *
 *  \param  pinfo[OUT]
 *          - firmware image information record
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *  \sa     struct qmifwinfo_s
 *
 *  \note   Device Supported: MC73xx\n
 *          Timeout: N/A\n
 *
 */
ULONG SLQSGetImageInfo_9x15(
    LPCSTR              path,
    BYTE                imgType,
    struct slqsfwinfo_s *pinfo );

/**
 *  This API is used to upgrade firmware on a MC73xx device. This API
 *  encapsulates all steps involved in the firmware download process. It is
 *  an alternative to any firmware download application.
 *  Hence it is a blocking API call. This API will not return until
 *  the entire process has been completed.
 *
 *  This API Performs the following steps:\n
 *  1. Verifies arguments.\n
 *  2. Retrieve and store the details of the firmware and the PRI file\n
 *  3. Enable device state change callback.\n
 *  4. Enable firmware download callback.\n
 *  5. Set Image preference on the device and reset the device.\n
 *  6. Wait for the firmware to download and device to become ready.\n
 *  7. Check the firmware update status. If fail, return an error.\n
 *  8. If update status is OK, check if current image preference and
 *     preferred image preference( from step 2 ) match\n
 *  9. If match, firmware download is successful.\n
 *  10. If do not match, repeat from step 5 once more.\n
 *  11. Disable callbacks and exit.\n
 *
 *  The call to this API blocks until step 7 or 11. This could be a significant
 *  amount of time ( in order of minutes ). Also note that the device
 *  state change callback and firmware download callback are used internally \n
 *  within this API. Hence the user application's instance of these callbacks
 *  (if any) are cleared. The user must re-enable these callbacks after a call
 *  to this API in order to use them.\n
 *
 *  \param  pDestinationPath[IN]
 *          - fully qualified path to firmware image to download. The path must\n
 *            end with a forward slash.
 *
 *  \return
 *          - eQCWWAN_ERR_INVALID_ARG - The path input does not contain any image
 *          - eQCWWAN_ERR_SWIIM_FW_UPDATE_FAIL - Upgrade( i.e. download to device ) failed
 *          - eQCWWAN_ERR_SWIIM_FW_UPDATE_SUCCESS - Upgrade succeeded and device online.
 *          - eQCWWAN_ERR_SWIIM_FW_PREFERENCE_MISMATCH - Upgrade succeeded but device offline
 *                                                       due to image preference mismatch
 *                                                       ( ref. syslogs for cause )
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   Timeout: NA\n
 *
 */
ULONG SLQSUpgradeFirmware9x15(
    CHAR *pDestinationPath );

/**
 *  Gets the boot loader version number
 *
 *  \param  bootversion[OUT]
 *          - boot loader version presented by a 4 byte integer 
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   Device Supported: MC9090/SL9090\n
 *          Timeout: 2 seconds
 *
 */
ULONG SLQSGetBootVersionNumber(ULONG *bootversion);

/**
 *  Check if SPKG format download is required for SL9090/MC9090
 *
 *  \param  none
 *
 *  \return return TRUE if required, otherwise, return FALSE
 *
 *  \note   Device Supported: MC9090/SL9090\n
 *          Timeout: 2 seconds
 *
 */
BOOL SLQSIsSpkgFormatRequired(void);

ULONG upgrade_mc77xx_fw(
    LPCSTR path );

/**
 * enumeration which lists the Device Series
 */
enum eGobiDeviceSeries
{
    eGOBI_DEV_SERIES_UNKNOWN = -1,   /* unknown */
    eGOBI_DEV_SERIES_NON_GOBI = 0,   /* Non Gobi */
    eGOBI_DEV_SERIES_G3K,            /* G3K */
    eGOBI_DEV_SERIES_SIERRA_GOBI,    /* MC9090 SL9090 */
    eGOBI_DEV_SERIES_9X15,           /* 9x15 */
    eGOBI_DEV_SERIES_9X30,           /* 9x30 */
    eGOBI_DEV_SERIES_9X07_9X50,      /* 9x07, 9x50 */
    eGobi_DEV_SERIES_MC83            /* MC83 */
};
/**
 * This structure contains the Device Series
 *
 *  \param  eGobiDeviceSeries
 *          - The number of device in the device series
 *
 *  \param  uResult
 *          -eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 */

struct sGetDeviceSeriesResult
{
    enum eGobiDeviceSeries eDevice;
    ULONG uResult;
};

/**
 *  Name    : eGetDeviceSeries
 *  \param  none
 *
 *  \return sGetDeviceSeriesResult
 *
 *  \note  Get Devie Series
 *
 */
void eGetDeviceSeries(struct sGetDeviceSeriesResult*);


/**
 * This structure contains the Carrier Image parameters.
 *
 *  \param  m_nCarrierId
 *          - Unique numeric carrier ID indicating the carrier that
 *            the following images belong to
 *
 *  \param  m_nFolderId
 *          - Unique numeric folder ID indicating the folder where the
 *            images should reside on the host storage.
 *
 *  \param  m_nStorage
 *          - Information of storage type
 *          - Values
 *            - 0 - Device
 *            - 1 - Host
 *
 *  \param  m_FwImageId
 *          - Firmware image ID
 *
 *  \param  m_FwBuildId
 *          - Firmware build ID
 *
 *  \param  m_PriImageId
 *          - PRI image ID
 *
 *  \param  m_PriBuildId
 *          - PRI build ID
 *
 */

struct SWI_STRUCT_CarrierImage
{
    ULONG     m_nCarrierId;
    ULONG     m_nFolderId;
    ULONG     m_nStorage;
    BYTE      m_FwImageId[16];
    BYTE      m_FwBuildId[32];
    BYTE      m_PriImageId[16];
    BYTE      m_PriBuildId[32];
};
/**
 * This API gets a list of all images stored on both the host and the device
 *
 *  \param  pNumOfItems
 *          - Number of Images{I/O]
 *
 *  \param  pCarrierImages[O]
 *          - See \ref SWI_STRUCT_CarrierImage
 *
 *  \param  pFolderPath
 *          - Path of Input folder [I]
 *
 *  \return TRUE/FALSE
 *
 *  \note  In case pFolderPath is invalid, API does not return invalid path error
 *         as SLQSSwiGetAllCarrierImages get carrier images from device also.
 *
 */
ULONG SLQSSwiGetAllCarrierImages(ULONG *pNumOfItems,
                             struct SWI_STRUCT_CarrierImage *pCarrierImages,
                             CHAR *pFolderPath);

/**
 * This API check device belongs to 9x15 series. 
 *
 *  \param  NA
 *
 *  \return TRUE/FALSE
 *
 *  \note  
 *
 */                             
BOOL Is9x15Device();

/**
 * This API check device belongs to 9x30 series. 
 *
 *  \param  NA
 *
 *  \return TRUE/FALSE
 *
 *  \note  
 *
 */                             
BOOL Is9x30Device(); 

/**
 * This API check device belongs to SL8092RD series. 
 *
 *  \param  NA
 *
 *  \return TRUE/FALSE
 *
 *  \note  
 *
 */                             
BOOL Is8092RespinDevice();
                            
#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* __GOBI_API_FMS_H__ */
