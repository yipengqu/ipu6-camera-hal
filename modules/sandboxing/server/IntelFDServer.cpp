/*
 * Copyright (C) 2019-2020 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "IntelFDServer"

#include "modules/sandboxing/server/IntelFDServer.h"

#include <pvl_types.h>

#include "CameraLog.h"
#include "iutils/Utils.h"

namespace icamera {
IntelFDServer::IntelFDServer() {
    mFaceDetection = std::unique_ptr<IntelFaceDetection>(new IntelFaceDetection());

    LOG1("@%s", __func__);
}

IntelFDServer::~IntelFDServer() {
    LOG1("@%s", __func__);
}

status_t IntelFDServer::init(void* pData, int dataSize) {
    LOG1("@%s, pData:%p, dataSize:%d", __func__, pData, dataSize);
    CheckError(pData == nullptr, UNKNOWN_ERROR, "@%s, pData is nullptr", __func__);
    CheckError(dataSize < static_cast<int>(sizeof(FaceDetectionInitParams)), UNKNOWN_ERROR,
               "buffer is small");

    return mFaceDetection->init(static_cast<FaceDetectionInitParams*>(pData), dataSize);
}

status_t IntelFDServer::run(void* pData, int dataSize, void* imageData) {
    PERF_CAMERA_ATRACE();
    TRACE_LOG_PROCESS("IntelFDServer", "runFaceDetection");
    LOG1("@%s, pData:%p, dataSize:%d, imageData:%p", __func__, pData, dataSize, imageData);
    CheckError(pData == nullptr, UNKNOWN_ERROR, "@%s, pData is nullptr", __func__);
    CheckError(dataSize < static_cast<int>(sizeof(FaceDetectionRunParams)), UNKNOWN_ERROR,
               "buffer is small");

    pvl_image image;
    FaceDetectionRunParams* pFdRunParams = static_cast<FaceDetectionRunParams*>(pData);
    mIpcFD.serverUnflattenRun(*pFdRunParams, imageData, &image);

    return mFaceDetection->run(&image, &pFdRunParams->results);
}

status_t IntelFDServer::deinit() {
    LOG1("@%s", __func__);
    return mFaceDetection->deinit();
}
} /* namespace icamera */
