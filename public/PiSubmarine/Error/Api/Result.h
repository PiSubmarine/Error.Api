#pragma once

#include <expected>

#include "PiSubmarine/Error/Api/Error.h"

namespace PiSubmarine::Error::Api
{
	template<typename T>
	using Result = std::expected<T, Error>;
}
