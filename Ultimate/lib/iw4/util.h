#pragma once

#define IW4_FUNCTION(FUNC_NAME, RETURN_TYPE, ARGUMENTS, ADDRESS) inline RETURN_TYPE(*FUNC_NAME) ARGUMENTS = reinterpret_cast<RETURN_TYPE(*) ARGUMENTS>(ADDRESS)
