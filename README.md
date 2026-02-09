# CMSTPLUA UAC Bypass

A Windows User Account Control (UAC) bypass technique using the undocumented `ICMLuaUtil` COM interface.

## Overview

This proof-of-concept demonstrates a UAC bypass that elevates a process from Medium Integrity Level to High Integrity Level without triggering a UAC prompt.

### Privilege Escalation Path

**Before:**
```
[+] Token IntegrityLevel = Medium
[+] Token IsElevated     = NO
[+] Token IsAdmin        = NO
```

**After:**
```
[+] Token IntegrityLevel = High
[+] Token IsElevated     = YES
[+] Token IsAdmin        = YES
```

## Technical Details

### Attack Vector

The bypass exploits the COM Elevation Moniker combined with an undocumented COM interface:

- **CLSID**: `{3E5FC7F9-9A51-4367-9063-A120244FBEC7}`
- **Interface**: `ICMLuaUtil` - `{6EDD6D74-C007-4E75-B76A-E5740995E24C}`
- **Elevation Moniker**: `Elevation:Administrator!new:{CLSID}`

### Execution Flow

1. **Process Masquerading**: Renames current process to `explorer.exe` in memory to bypass trust checks
2. **COM Elevation**: Uses `CoGetObject()` with Elevation Moniker to instantiate elevated COM object
3. **Privileged Execution**: Calls `ICMLuaUtil::ShellExec()` to launch target executable with High IL
4. **DllHost Spawning**: The target process is spawned by `DllHost.exe` running at High Integrity Level

## Requirements

- **OS**: Windows 10/11 (tested on Windows 10 1903+)
- **Privileges**: Medium Integrity Level
- **Account**: User must be member of Administrators group
- **Compiler**: MSVC (Visual Studio 2019+) or MinGW with C++20 support

### Basic Usage
```bash
CMSTPLUA_UAC_Bypass.exe C:\Windows\System32\cmd.exe
```

## Legal Disclaimer

**FOR EDUCATIONAL AND AUTHORIZED SECURITY RESEARCH ONLY**

This tool is provided for:
- Educational purposes to understand Windows security mechanisms
- Authorized penetration testing in controlled environments
- Security research and vulnerability analysis
- Red team exercises with proper authorization

**⚡ Remember**: With great power comes great responsibility. Use ethically.
