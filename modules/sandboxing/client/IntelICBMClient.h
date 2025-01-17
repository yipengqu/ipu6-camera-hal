/*
 * Copyright (C) 2022 Intel Corporation
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

#pragma once

#include <vector>

#include "CameraBuffer.h"
#include "Parameters.h"
#include "PlatformData.h"
#include "src/icbm/ICBMTypes.h"

namespace icamera {

class IntelICBM {
 public:
    IntelICBM() {}
    ~IntelICBM(){};

    Result setup(ICBMInitInfo* initParam);
    void shutdown();
    Result processFrame(const ImageInfo& iii, const ImageInfo& iio, const ICBMReqInfo& reqInfo);

 private:
    Result initRunInfoBuffer();

    IntelAlgoCommon mCommon;
    ShmMemInfo mRunInfoMem;

    DISALLOW_COPY_AND_ASSIGN(IntelICBM);
};
}  // namespace icamera
