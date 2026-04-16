#pragma once

#include <system_error>

#include "PiSubmarine/Error/Api/Error.h"

namespace PiSubmarine::Error::Api
{
	[[nodiscard]] inline Error MakeError(const ErrorCondition condition) noexcept
	{
		return Error{condition, {}};
	}

	[[nodiscard]] inline Error MakeError(const ErrorCondition condition, const std::error_code cause) noexcept
	{
		return Error{condition, cause};
	}
}
