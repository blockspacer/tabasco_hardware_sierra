//  BEGIN CCCT SECTION
/*  -------------------------------------------------------------------------
    Copyright (C) 2014 Intel Mobile Communications GmbH

         Sec Class: Intel Confidential (IC)
    ----------------------------------------------------------------------
    Revision Information:
       $File name:  /msw_tools/FlashTool/libFlsTool/inc/tool_versions.h $
       $CC-Version: .../oint_tools_flashtoole2_01/1 $
       $Date:       2014-03-13    15:39:01 UTC $
    ----------------------------------------------------------------------
    by CCCT (0.12c)
    ---------------------------------------------------------------------- */
//  END CCCT SECTION

#ifndef __TOOL_VERSIONS_H__
#define __TOOL_VERSIONS_H__

/* Tool Versions for all the tools
1st Nibble : Major version
2nd Nibble : Minor Version
Eg: 0x00000001 means version 0.1
*/
#define PRGHANDLER_TOOL_REQ_VER    0x00020002
#define PRGSEQUENCER_TOOL_REQ_VER  0x00020003
#define MAKEPRG_TOOL_REQ_VER       0x00020003
#define HEXTOFLS_TOOL_REQ_VER      0x00020000
#define FLSSIGN_TOOL_REQ_VER       0x00020000
#define DWDTOHEX_TOOL_REQ_VER      0x00020000
#define FLASHTOOL_TOOL_REQ_VER     0x00040000
#define STORAGETOOL_TOOL_REQ_VER   0x00010000 // Removed from Version Check
#define FLSTOHEADER_TOOL_REQ_VER   0x00020000
#define BOOT_CORE_TOOL_REQ_VER     0x00020000
#define EBL_TOOL_REQ_VER           0x00020000
#define FLSTONAND_TOOL_REQ_VER     0x00020000

#endif


