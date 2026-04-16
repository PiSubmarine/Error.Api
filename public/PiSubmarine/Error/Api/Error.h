#pragma once

#include <system_error>

#include "PiSubmarine/Error/Api/ErrorCondition.h"

namespace PiSubmarine::Error::Api
{
	struct Error
	{
		ErrorCondition Condition{};
		std::error_code Cause{};

		[[nodiscard]] bool HasCause() const noexcept
		{
			return static_cast<bool>(Cause);
		}

		[[nodiscard]] bool operator==(const Error&) const = default;
	};
}
