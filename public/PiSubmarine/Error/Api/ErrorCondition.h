#pragma once

namespace PiSubmarine::Error::Api
{
	enum class ErrorCondition
	{
		ContractError,
		CommunicationError,
		DeviceError,
		NotFound,
		NotReady,
		PermissionDenied,
		ResourceExhausted,
		UnknownError
	};
}
