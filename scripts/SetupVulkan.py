# import os
# import subprocess
# import sys
# from pathlib import Path
# import Utils
# from io import BytesIO
# from urllib.request import urlopen
# from zipfile import ZipFile
# VULKAN_SDK = os.environ.get('VULKAN_SDK')
# # VULKAN_SDK_INSTALLER_URL = 'https://sdk.lunarg.com/sdk/download/1.2.170.0/windows/vulkan_sdk.exe'
# VULKAN_SDK_INSTALLER_URL = 'https://sdk.lunarg.com/sdk/download/1.2.198.1/windows/VulkanSDK-1.2.198.1-Installer.exe'
# RAZOR_VULKAN_VERSION = '1.2.198.1'
# VULKAN_SDK_EXE_PATH = 'Razor/vendor/VulkanSDK/VulkanSDK.exe'
# def InstallVulkanSDK():
#     print('Downloading {} to {}'.format(VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_EXE_PATH))
#     Utils.DownloadFile(VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_EXE_PATH)
#     print("Done!")
#     print("Running Vulkan SDK installer...")
#     os.startfile(os.path.abspath(VULKAN_SDK_EXE_PATH))
#     print("Re-run this script after installation")
# def InstallVulkanPrompt():
#     print("Would you like to install the Vulkan SDK?")
#     install = Utils.YesOrNo()
#     if (install):
#         InstallVulkanSDK()
#         quit()
# def CheckVulkanSDK():
#     if (VULKAN_SDK is None):
#         print("You don't have the Vulkan SDK installed!")
#         InstallVulkanPrompt()
#         return False
#     elif (RAZOR_VULKAN_VERSION not in VULKAN_SDK):
#         print(f"Located Vulkan SDK at {VULKAN_SDK}")
#         print(f"You don't have the correct Vulkan SDK version! (Razor requires {RAZOR_VULKAN_VERSION})")
#         InstallVulkanPrompt()
#         return False
    
#     print(f"Correct Vulkan SDK located at {VULKAN_SDK}")
#     return True
# # VulkanSDKDebugLibsURL = 'https://files.lunarg.com/SDK-1.2.170.0/VulkanSDK-1.2.170.0-DebugLibs.zip'
# VulkanSDKDebugLibsURL = 'https://sdk.lunarg.com/sdk/download/1.2.198.1/windows/VulkanRT-1.2.198.1-Components.zip'
# OutputDirectory = "Razor/vendor/VulkanSDK"
# TempZipFile = f"{OutputDirectory}/VulkanSDK.zip"
# def CheckVulkanSDKDebugLibs():
#     shadercdLib = Path(f"{OutputDirectory}/Lib/shaderc_sharedd.lib")
#     if (not shadercdLib.exists()):
#         print(f"No Vulkan SDK debug libs found. (Checked {shadercdLib})")
#         print("Downloading", VulkanSDKDebugLibsURL)
#         with urlopen(VulkanSDKDebugLibsURL) as zipresp:
#             with ZipFile(BytesIO(zipresp.read())) as zfile:
#                 zfile.extractall(OutputDirectory)
#     print(f"Vulkan SDK debug libs located at {OutputDirectory}")
#     return True


import os
import subprocess
import sys
from pathlib import Path
import Utils
from io import BytesIO
from urllib.request import urlopen
from zipfile import ZipFile

VULKAN_SDK = os.environ.get('VULKAN_SDK')


VULKAN_SDK_INSTALLER_URL = 'https://sdk.lunarg.com/sdk/download/1.2.198.1/windows/VulkanSDK-1.2.198.1-Installer.exe'
RAZOR_VULKAN_VERSION = '1.2.198.1'
VULKAN_SDK_EXE_PATH = 'Razor/vendor/VulkanSDK/VulkanSDK.exe'

def InstallVulkanSDK():
    print(f'Downloading {VULKAN_SDK_INSTALLER_URL} to {VULKAN_SDK_EXE_PATH}')
    Utils.DownloadFile(VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_EXE_PATH)
    print("Done!")
    print("Running Vulkan SDK installer...")
    os.startfile(os.path.abspath(VULKAN_SDK_EXE_PATH))
    print("Re-run this script after installation")

def InstallVulkanPrompt():
    print("Would you like to install the Vulkan SDK?")
    install = Utils.YesOrNo()
    if install:
        InstallVulkanSDK()
        quit()

def CheckVulkanSDK():
    if VULKAN_SDK is None:
        print("You don't have the Vulkan SDK installed!")
        InstallVulkanPrompt()
        return False
    elif RAZOR_VULKAN_VERSION not in VULKAN_SDK:
        print(f"Located Vulkan SDK at {VULKAN_SDK}")
        print(f"You don't have the correct Vulkan SDK version! (Razor requires {RAZOR_VULKAN_VERSION})")
        InstallVulkanPrompt()
        return False
    
    print(f"Correct Vulkan SDK located at {VULKAN_SDK}")
    return True

VulkanSDKDebugLibsURL = 'https://sdk.lunarg.com/sdk/download/1.2.198.1/windows/VulkanRT-1.2.198.1-Components.zip'
OutputDirectory = "Razor/vendor/VulkanSDK"
TempZipFile = f"{OutputDirectory}/VulkanSDK.zip"

def CheckVulkanSDKDebugLibs():
    shadercdLib = Path(f"{OutputDirectory}/Lib/shaderc_sharedd.lib")
    
    # Check if the Vulkan SDK debug libraries exist, and download if they don't
    if not shadercdLib.exists():
        print(f"No Vulkan SDK debug libs found. (Checked {shadercdLib})")
        print(f"Downloading {VulkanSDKDebugLibsURL}")
        try:
            with urlopen(VulkanSDKDebugLibsURL) as zipresp:
                with ZipFile(BytesIO(zipresp.read())) as zfile:
                    zfile.extractall(OutputDirectory)
            print(f"Vulkan SDK debug libs located at {OutputDirectory}")
        except Exception as e:
            print(f"Error downloading or extracting Vulkan SDK debug libs: {e}")
            return False
    else:
        print(f"Vulkan SDK debug libs already located at {OutputDirectory}")
    
    return True