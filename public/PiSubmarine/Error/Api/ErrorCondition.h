#pragma once

namespace PiSubmarine::Error::Api
{
	enum class ErrorCondition
	{
		ContractError,
		CommunicationError,
		DeviceError,
		NotReady,
		UnknownError
	};
}
