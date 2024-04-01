#include <efi.h>
#include <efilib.h>

#include <axboot.h>
#include <print.h>
#include <file.h>

VOID *
FileRead(CHAR16 *Filename, UINTN *FileSize)
{
	EFI_GUID LoadedImageProtocolGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
	EFI_GUID SimpleFileSystemProtocolGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
	EFI_GUID FileInfoGuid = EFI_FILE_INFO_ID;

	EFI_LOADED_IMAGE_PROTOCOL *LoadedImage = NULL;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem = NULL;
	EFI_FILE_PROTOCOL *RootDirectory = NULL;

	VOID *Buffer = NULL;
	UINTN BufferSize = sizeof(EFI_FILE_INFO);
	EFI_FILE_PROTOCOL *File = NULL;
	EFI_FILE_INFO FileInfo;

	EFI_STATUS Status = EFI_SUCCESS;

	Status = g_SystemTable->BootServices->OpenProtocol(g_ImageHandle,
				&LoadedImageProtocolGuid,
				(VOID **)&LoadedImage,
				g_ImageHandle,
				NULL,
				EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
	if (EFI_ERROR(Status)) {
		EfiPrint(L"ERROR: Couldn't open Loaded Image Protocol.\r\n");
		goto cleanup;
	}

	Status = g_SystemTable->BootServices->OpenProtocol(LoadedImage->DeviceHandle,
				&SimpleFileSystemProtocolGuid,
				(VOID **)&FileSystem,
				g_ImageHandle,
				NULL,
				EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
	if (EFI_ERROR(Status)) {
		EfiPrint(L"ERROR: Couldn't open Simple File System Protocol.\r\n");
		goto cleanup;
	}

	Status = FileSystem->OpenVolume(FileSystem, &RootDirectory);
	if (EFI_ERROR(Status)) {
		EfiPrint(L"ERROR: Couldn't open root directory volume.\r\n");
		goto cleanup;
	}

	Status = RootDirectory->Open(RootDirectory, &File, Filename, EFI_FILE_MODE_READ, 0);
	if (EFI_ERROR(Status)) {
		EfiPrint(L"ERROR: Couldn't open file '%s'.\r\n", Filename);
		goto cleanup;
	}

	Status = File->GetInfo(File, &FileInfoGuid, &BufferSize, &FileInfo);
	if (EFI_ERROR(Status)) {
		EfiPrint(L"ERROR: Failed to get file info ('%s') - %d.\r\n", Filename, Status);
		goto cleanup;
	}

	EfiPrint(L"File size: %u\r\n", FileInfo.FileSize);

	BufferSize = FileInfo.FileSize;
	Status = g_SystemTable->BootServices->AllocatePool(EfiLoaderData, BufferSize, &Buffer);
	if (EFI_ERROR(Status) || (BufferSize != FileInfo.FileSize)) {
		EfiPrint(L"ERROR: Failed to allocate memory for file '%s'.\r\n", Filename);
		goto cleanup;
	}

	Status = File->Read(File, &BufferSize, Buffer);
	if (EFI_ERROR(Status) || (BufferSize != FileInfo.FileSize)) {
		EfiPrint(L"ERROR: Failed to read file '%s'.\r\n", Filename);
		goto cleanup;
	}

	*FileSize = BufferSize;

cleanup:
	File->Close(File);
	RootDirectory->Close(RootDirectory);

	g_SystemTable->BootServices->CloseProtocol(LoadedImage->DeviceHandle,
		&SimpleFileSystemProtocolGuid,
		g_ImageHandle,
		NULL);

	g_SystemTable->BootServices->CloseProtocol(g_ImageHandle,
		&LoadedImageProtocolGuid,
		g_ImageHandle,
		NULL);

	return Buffer;
}
