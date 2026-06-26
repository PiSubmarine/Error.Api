#pragma once

#include <string_view>

#include "PiSubmarine/Error/Api/ErrorCondition.h"

namespace PiSubmarine::Error::Api
{
    [[nodiscard]] constexpr std::string_view ToStringView(const ErrorCondition condition) noexcept
    {
        switch (condition)
        {
            case ErrorCondition::ContractError:
                return "contract error";
            case ErrorCondition::CommunicationError:
                return "communication error";
            case ErrorCondition::DeviceError:
                return "device error";
            case ErrorCondition::NotFound:
                return "not found";
            case ErrorCondition::NotReady:
                return "not ready";
            case ErrorCondition::PermissionDenied:
                return "permission denied";
            case ErrorCondition::ResourceExhausted:
                return "resource exhausted";
            case ErrorCondition::UnknownError:
                return "unknown error";
        }

        return "unrecognized error";
    }
}
