#include <gtest/gtest.h>

#include <string>
#include <system_error>

#include "PiSubmarine/Error/Api/MakeError.h"
#include "PiSubmarine/Error/Api/Result.h"
#include "PiSubmarine/Error/Api/ToStringView.h"

namespace PiSubmarine::Error::Api
{
	namespace
	{
		enum class TestCause
		{
			Example = 1
		};

		class TestCauseCategory final : public std::error_category
		{
		public:
			[[nodiscard]] const char* name() const noexcept override
			{
				return "PiSubmarine.Error.Api.Test";
			}

			[[nodiscard]] std::string message(const int condition) const override
			{
				switch (static_cast<TestCause>(condition))
				{
				case TestCause::Example:
					return "example cause";
				}

				return "unknown test cause";
			}
		};

		[[nodiscard]] const std::error_category& GetTestCauseCategory() noexcept
		{
			static const TestCauseCategory category;
			return category;
		}

		[[nodiscard]] std::error_code MakeTestCause(const TestCause cause) noexcept
		{
			return {static_cast<int>(cause), GetTestCauseCategory()};
		}
	}

	TEST(ErrorTest, MakeErrorWithoutCauseLeavesCauseEmpty)
	{
		const auto error = MakeError(ErrorCondition::CommunicationError);

		EXPECT_EQ(error.Condition, ErrorCondition::CommunicationError);
		EXPECT_FALSE(error.HasCause());
		EXPECT_FALSE(error.Cause);
	}

	TEST(ErrorTest, MakeErrorWithCausePreservesCause)
	{
		const auto cause = MakeTestCause(TestCause::Example);
		const auto error = MakeError(ErrorCondition::DeviceError, cause);

		EXPECT_EQ(error.Condition, ErrorCondition::DeviceError);
		EXPECT_TRUE(error.HasCause());
		EXPECT_EQ(error.Cause, cause);
		EXPECT_EQ(error.Cause.category().name(), std::string("PiSubmarine.Error.Api.Test"));
		EXPECT_EQ(error.Cause.message(), std::string("example cause"));
	}

	TEST(ErrorTest, EqualityUsesConditionAndCause)
	{
		const auto cause = MakeTestCause(TestCause::Example);

		EXPECT_EQ(MakeError(ErrorCondition::UnknownError), MakeError(ErrorCondition::UnknownError));
		EXPECT_EQ(MakeError(ErrorCondition::ContractError, cause), MakeError(ErrorCondition::ContractError, cause));
		EXPECT_NE(MakeError(ErrorCondition::ContractError), MakeError(ErrorCondition::CommunicationError));
		EXPECT_NE(MakeError(ErrorCondition::ContractError), MakeError(ErrorCondition::ContractError, cause));
	}

	TEST(ErrorTest, SupportsGenericPersistenceRelatedConditions)
	{
		EXPECT_EQ(MakeError(ErrorCondition::NotFound).Condition, ErrorCondition::NotFound);
		EXPECT_EQ(MakeError(ErrorCondition::PermissionDenied).Condition, ErrorCondition::PermissionDenied);
		EXPECT_EQ(MakeError(ErrorCondition::ResourceExhausted).Condition, ErrorCondition::ResourceExhausted);
	}

	TEST(ErrorTest, ToStringViewReturnsStableHumanReadableNames)
	{
		static_assert(ToStringView(ErrorCondition::ContractError) == "contract error");
		static_assert(ToStringView(ErrorCondition::CommunicationError) == "communication error");
		static_assert(ToStringView(ErrorCondition::DeviceError) == "device error");
		static_assert(ToStringView(ErrorCondition::NotFound) == "not found");
		static_assert(ToStringView(ErrorCondition::NotReady) == "not ready");
		static_assert(ToStringView(ErrorCondition::PermissionDenied) == "permission denied");
		static_assert(ToStringView(ErrorCondition::ResourceExhausted) == "resource exhausted");
		static_assert(ToStringView(ErrorCondition::UnknownError) == "unknown error");

		EXPECT_EQ(ToStringView(ErrorCondition::ContractError), std::string_view("contract error"));
		EXPECT_EQ(ToStringView(ErrorCondition::NotReady), std::string_view("not ready"));
	}

	TEST(ErrorTest, ResultAliasWorksForValueAndVoid)
	{
		const Result<int> valueResult = 42;
		const Result<void> voidResult{};
		const Result<int> errorResult = std::unexpected(MakeError(ErrorCondition::UnknownError));

		ASSERT_TRUE(valueResult.has_value());
		EXPECT_EQ(valueResult.value(), 42);

		ASSERT_TRUE(voidResult.has_value());

		ASSERT_FALSE(errorResult.has_value());
		EXPECT_EQ(errorResult.error().Condition, ErrorCondition::UnknownError);
	}
}
