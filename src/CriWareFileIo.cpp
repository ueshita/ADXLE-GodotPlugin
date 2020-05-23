/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2015-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Godot Engine
 * Module   : File I/O Interface
 * File     : CriWareFileIo.cpp
 *
 ****************************************************************************/

/***************************************************************************
 * インクルード
 * Header files
 ***************************************************************************/
/* モジュールヘッダ */
#include "CriWareFileIo.h"

/* CRIWAREプラグインヘッダ */
#include <cri_le_file_system.h>

/* ANSI Cヘッダ */
#include <algorithm>
#include <string.h>
#include <assert.h>

/* Godot Engine関連ヘッダ */
#include <File.hpp>

/***************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 ***************************************************************************/

/***************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 ***************************************************************************/

/***************************************************************************
 * 型定義
 * Type definitions
 ***************************************************************************/
/* ファイルハンドル */
struct CriWareFile
{
	godot::Ref<godot::File> FileHandle;	/* ネイティブファイルハンドル	*/
	int64_t FileSize = 0;				/* ファイルサイズ				*/
	int64_t ReadSize = 0;				/* 最終読み込みサイズ			*/
	int64_t WriteSize = 0;				/* 最終書き込みサイズ			*/

	/* インターフェース登録用関数 */
	/* Functions for the interface registration */
	static CriFsIoError Exists(const CriChar8 *Filename, CriBool *OutResult);
	static CriFsIoError Open(const CriChar8 *Filename,
		CriFsFileMode mode, CriFsFileAccess access, CriFsFileHn *OutFile);
	static CriFsIoError Close(CriFsFileHn InFile);
	static CriFsIoError GetFileSize(CriFsFileHn InFile, CriSint64 *FileSize);
	static CriFsIoError Read(CriFsFileHn InFile,
		CriSint64 Offset, CriSint64 ReadSize, void *Buffer, CriSint64 BufferSize);
	static CriFsIoError IsReadComplete(CriFsFileHn InFile, CriBool *OutResult);
	static CriFsIoError GetReadSize(CriFsFileHn InFile, CriSint64 *ReadSize);
	static CriFsIoError Write(CriFsFileHn InFile,
		CriSint64 Offset, CriSint64 WriteSize, void *Buffer, CriSint64 BufferSize);
	static CriFsIoError IsWriteComplete(CriFsFileHn InFile, CriBool *OutResult);
	static CriFsIoError GetWriteSize(CriFsFileHn InFile, CriSint64 *WriteSize);
	static CriFsIoError GetNativeFileHandle(CriFsFileHn InFile, void **native_filehn);
};

/***************************************************************************
 * 変数宣言
 * Variable declarations
 ***************************************************************************/

/***************************************************************************
 * 関数宣言
 * Function declarations
 ***************************************************************************/

/***************************************************************************
 * 変数定義
 * Variable definitions
 ***************************************************************************/

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/*==========================================================================
 * I/Oインターフェース選択関数
 * I/O interface selection function
 *=========================================================================*/
CriError CriWareFileIo::SelectIo(const CriChar8 *Filename,
	CriFsDeviceId *DeviceId, CriFsIoInterfacePtr *IoInterface)
{
	/* I/O処理インターフェース */
	/* I/O processing interface */
	static CriFsIoInterface CriFileIoInterface = {
		CriWareFile::Exists,
		NULL,
		NULL,
		CriWareFile::Open,
		CriWareFile::Close,
		CriWareFile::GetFileSize,
		CriWareFile::Read,
		CriWareFile::IsReadComplete,
		NULL,
		CriWareFile::GetReadSize,
		CriWareFile::Write,
		CriWareFile::IsWriteComplete,
		NULL,
		CriWareFile::GetWriteSize,
		NULL,
		NULL,
		CriWareFile::GetNativeFileHandle
	};

	/* 引数のチェック */
	/* Check the arguments */
	assert(Filename != NULL);
	assert(DeviceId != NULL);
	assert(IoInterface != NULL);

	/* デフォルトのデバイスIDを使用 */
	/* 備考）本サンプルでは1つのデバイスのみを想定 */
    /* The default device ID is specified */
    /* Note: One device is used in this sample */
	(*DeviceId) = CRIFS_DEFAULT_DEVICE;

	/* I/OインターフェースとしてGCriFileIoInterfaceを使用 */
    /* GCriFileIoInterface is used as the I/O interface */
	(*IoInterface) = &CriFileIoInterface;

	return (CRIERR_OK);
}

/*==========================================================================
 * インターフェース登録用関数
 * Interface registration functions
 *=========================================================================*/
/* ファイルの有無の確認 */
/* Check whether the file exists */
CriFsIoError CriWareFile::Exists(const CriChar8 *Filename, CriBool *OutResult)
{
	/* 引数のチェック */
	/* Check the arguments */
	assert(Filename != NULL);
	assert(OutResult != NULL);

	godot::String path(Filename);
#if defined(_WIN32)
	path = path.replace("\\", "/");
#endif

	/* ファイルの有無をチェック */
	/* Check whether the file exists */
	godot::Ref<godot::File> FileHandle(godot::File::_new());
	if (FileHandle->file_exists(path)) {
		(*OutResult) = CRI_TRUE;
	} else {
		(*OutResult) = CRI_FALSE;
	}

	return (CRIFS_IO_ERROR_OK);
}

CriFsIoError CriWareFile::Open(const CriChar8 *Filename,
	CriFsFileMode Mode, CriFsFileAccess Access, CriFsFileHn *OutFile)
{
	CriWareFile *File;

	/* 引数のチェック */
	/* Check the arguments */
	assert(Filename != NULL);
	assert(OutFile != NULL);

	/* 出力値の初期化 */
	(*OutFile) = NULL;

	godot::String path(Filename);
#if defined(_WIN32)
	path = path.replace("\\", "/");
#endif

	/* 追記かどうかのチェック */
	bool bAppend;
	if (Mode == CRIFS_FILE_MODE_APPEND) {
		bAppend = true;
	} else {
		bAppend = false;
	}

	/* リードの可否をチェック */
	bool bAllowRead;
	if (Access == CRIFS_FILE_ACCESS_WRITE) {
		bAllowRead = false;
	} else {
		bAllowRead = true;
	}

	/* ファイルハンドル領域の確保 */
	/* Allocate a file handle area */
	File = new CriWareFile();
	if (File == NULL) {
		return (CRIFS_IO_ERROR_NG);
	}
	File->FileHandle.instance();

	/* ファイルのオープン */
	/* Open a file */
	godot::Error error = godot::Error::OK;
	if (Access == CRIFS_FILE_ACCESS_READ) {
		error = File->FileHandle->open(path, godot::File::READ);
	} else {
		error = File->FileHandle->open(path, godot::File::WRITE);
	}

	if (error != godot::Error::OK) {
		delete File;
		return (CRIFS_IO_ERROR_NG);
	}

	/* ファイルサイズの取得 */
	/* Get the file size */
	File->FileSize = File->FileHandle->get_len();

	/* ハンドルの保存 */
	/* Store the file handle */
	(*OutFile) = File;

	return (CRIFS_IO_ERROR_OK);
}

CriFsIoError CriWareFile::Close(CriFsFileHn InFile)
{
	CriWareFile *File;

	/* 引数のチェック */
	/* Check the arguments */
	assert(InFile != NULL);

	/* 変数の初期化 */
	/* Initialize variables */
	File = (CriWareFile *)InFile;

	/* ファイルのクローズ */
	/* Close the file */
	if (File->FileHandle.is_valid()) {
		File->FileHandle->close();
		File->FileHandle.unref();
	}

	/* ハンドル領域の解放 */
	/* Deallocate the handle area */
	delete File;

	return (CRIFS_IO_ERROR_OK);
}

CriFsIoError CriWareFile::GetFileSize(CriFsFileHn InFile, CriSint64 *FileSize)
{
	CriWareFile *File;

	/* 引数のチェック */
	/* Check the arguments */
	assert(InFile != NULL);
	assert(FileSize != NULL);

	/* 変数の初期化 */
	/* Initialize variables */
	File = (CriWareFile *)InFile;

	/* ファイルサイズの保存 */
	/* Store the file size */
	(*FileSize) = File->FileSize;

	return (CRIFS_IO_ERROR_OK);
}

CriFsIoError CriWareFile::Read(CriFsFileHn InFile,
	CriSint64 Offset, CriSint64 ReadSize, void *Buffer, CriSint64 BufferSize)
{
	CriWareFile *File;

	/* 引数のチェック */
	/* Check the arguments */
	assert(InFile != NULL);
	assert(Offset >= 0);
	assert(ReadSize >= 0);
	assert(Buffer != NULL);
	assert(BufferSize >= 0);

	/* 変数の初期化 */
	/* Initialize variables */
	File = (CriWareFile *)InFile;

	/* 読み込みサイズの計算 */
	ReadSize = std::min(ReadSize, BufferSize);
	ReadSize = std::min(ReadSize, (CriSint64)File->FileSize - Offset);

	/* 読み込みが不要な場合は何もしない */
	if (ReadSize <= 0) {
		File->ReadSize = 0;
		return (CRIFS_IO_ERROR_OK);
	}

	/* 読み込み開始位置まで移動 */
	/* Move to a position for starting file read */
	File->FileHandle->seek(Offset);

	/* データの読み込み */
	/* Read data */
	auto ByteArray = File->FileHandle->get_buffer(ReadSize);
	memcpy(Buffer, ByteArray.read().ptr(), ReadSize);

	/* 読み込みサイズの保存 */
	/* Store the read size */
	File->ReadSize = ReadSize;

	return (CRIFS_IO_ERROR_OK);
}

CriFsIoError CriWareFile::IsReadComplete(CriFsFileHn InFile, CriBool *OutResult)
{
	/* 引数のチェック */
	/* Check the arguments */
	assert(InFile != NULL);
	assert(OutResult != NULL);

	/* 同期I/Oで実装しているので常にCRI_TRUEを返す */
	/* Always return TRUE as it is implemented as synchronus I/O */
	(*OutResult) = CRI_TRUE;

	return (CRIFS_IO_ERROR_OK);
}

CriFsIoError CriWareFile::GetReadSize(CriFsFileHn InFile, CriSint64 *ReadSize)
{
	CriWareFile *File;

	/* 引数のチェック */
	/* Check the arguments */
	assert(InFile != NULL);
	assert(ReadSize != NULL);

	/* 変数の初期化 */
	/* Initialize variables */
	File = (CriWareFile *)InFile;

	/* ファイルサイズの保存 */
	/* Store the file size */
	(*ReadSize) = File->ReadSize;

	return (CRIFS_IO_ERROR_OK);
}

CriFsIoError CriWareFile::Write(CriFsFileHn InFile,
	CriSint64 Offset, CriSint64 WriteSize, void *Buffer, CriSint64 BufferSize)
{
	CriWareFile *File;
	int64_t SeekPos;

	/* 引数のチェック */
	/* Check the arguments */
	assert(InFile != NULL);
	assert(Offset >= 0);
	assert(WriteSize >= 0);
	assert(Buffer != NULL);
	assert(BufferSize >= 0);

	/* 変数の初期化 */
	/* Initialize variables */
	File = (CriWareFile *)InFile;

	/* 書き込みサイズの計算 */
	WriteSize = std::min(WriteSize, BufferSize);

	/* 書き込みが不要な場合は何もしない */
	if (WriteSize <= 0) {
		File->WriteSize = 0;
		return (CRIFS_IO_ERROR_OK);
	}

	/* 書き込み開始位置まで移動 */
	/* Move to a position for starting file write */
	File->FileHandle->seek(Offset);

	/* データの書き込み */
	/* Write data */
	godot::PoolByteArray ByteArray;
	ByteArray.resize(WriteSize);
	memcpy(ByteArray.write().ptr(), Buffer, WriteSize);
	File->FileHandle->store_buffer(ByteArray);

	/* 書き込みサイズの保存 */
	/* Store the write size */
	File->WriteSize = WriteSize;

	/* ファイルサイズの補正 */
	/* Correct file size */
	SeekPos = Offset + WriteSize;
	if (File->FileSize < SeekPos) {
		File->FileSize = SeekPos;
	}

	return (CRIFS_IO_ERROR_OK);
}

CriFsIoError CriWareFile::IsWriteComplete(CriFsFileHn InFile, CriBool *OutResult)
{
	/* 引数のチェック */
	/* Check the arguments */
	assert(InFile != NULL);
	assert(OutResult != NULL);

	/* 同期I/Oで実装しているので常にCRI_TRUEを返す */
	/* Always return TRUE as it is implemented as synchronus I/O */
	(*OutResult) = CRI_TRUE;

	return (CRIFS_IO_ERROR_OK);
}

CriFsIoError CriWareFile::GetWriteSize(CriFsFileHn InFile, CriSint64 *WriteSize)
{
	CriWareFile *File;

	/* 引数のチェック */
	/* Check the arguments */
	assert(InFile != NULL);
	assert(WriteSize != NULL);

	/* 変数の初期化 */
	/* Initialize variables */
	File = (CriWareFile *)InFile;

	/* ファイルサイズの保存 */
	/* Store the file size */
	(*WriteSize) = File->WriteSize;

	return (CRIFS_IO_ERROR_OK);
}

/* ネイティブファイルハンドルの取得 */
/* Get a native file handle */
CriFsIoError CriWareFile::GetNativeFileHandle(CriFsFileHn InFile, void **native_filehn)
{
	CriWareFile *File;

	/* 引数のチェック */
	/* Check the arguments */
	assert(InFile != NULL);
	assert(native_filehn);

	/* 変数の初期化 */
	/* Initialize variables */
	File = (CriWareFile *)InFile;

	/* ファイルポインタの保存 */
	/* Store the file pointer */
	(*native_filehn) = (void *)File->FileHandle.ptr();

	return (CRIFS_IO_ERROR_OK);
}

/* --- end of file --- */
