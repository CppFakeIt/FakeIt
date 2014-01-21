#include "tpunit++.hpp"
#include "mock4cpp.h"
#include <string>

struct BasicVerification: tpunit::TestFixture {
	BasicVerification() :
			tpunit::TestFixture(
			//
					TEST(BasicVerification::verify_should_not_throw_exception_if_method_was_called), //
					TEST(BasicVerification::verify_should_throw_MethodCallVerificationException_if_method_was_not_called), //
					TEST(BasicVerification::verify_should_throw_MethodCallVerificationException_if_method_was_not_stubbed), //
					TEST(BasicVerification::verify_method_was_called_at_least_once), //
					TEST(BasicVerification::verify_method_was_called_exactly_once), //
					TEST(BasicVerification::verify_method_was_never_called), //
					TEST(BasicVerification::verify_method_was_called_exactly_x_times), //
					TEST(BasicVerification::should_throw_IllegalArgumentException_on_negative_times_argument), //
					TEST(BasicVerification::verify_with_filter),//
					TEST(BasicVerification::verify_concatenated_sequence),
					TEST(BasicVerification::verify_repeated_sequence)
					)  //
	{
	}

	struct SomeInterface {
		virtual int func(int) = 0;
		virtual void proc(int) = 0;
	};

	void verify_should_throw_MethodCallVerificationException_if_method_was_not_called() {
		Mock<SomeInterface> mock;
		Stub(mock[&SomeInterface::func], mock[&SomeInterface::proc]);
		ASSERT_THROW(Verify(mock[&SomeInterface::func]), mock4cpp::MethodCallVerificationException);
		ASSERT_THROW(Verify(mock[&SomeInterface::proc]), mock4cpp::MethodCallVerificationException);
	}

	void verify_should_throw_MethodCallVerificationException_if_method_was_not_stubbed() {
		Mock<SomeInterface> mock;
		ASSERT_THROW(Verify(mock[&SomeInterface::func]), mock4cpp::MethodCallVerificationException);
		ASSERT_THROW(Verify(mock[&SomeInterface::proc]), mock4cpp::MethodCallVerificationException);
	}

	void verify_should_not_throw_exception_if_method_was_called() {
		Mock<SomeInterface> mock;
		Stub(mock[&SomeInterface::func], mock[&SomeInterface::proc]);
		SomeInterface &i = mock.get();
		i.func(1);
		i.proc(1);
		Verify(mock[&SomeInterface::func]);
		Verify(mock[&SomeInterface::proc]);
	}

	void verify_method_was_called_at_least_once() {
		Mock<SomeInterface> mock;

		ASSERT_THROW(Verify(mock[&SomeInterface::func]), mock4cpp::MethodCallVerificationException);
		ASSERT_THROW(Verify(mock[&SomeInterface::proc]), mock4cpp::MethodCallVerificationException);

		Stub(mock[&SomeInterface::func], mock[&SomeInterface::proc]);
		SomeInterface &i = mock.get();
		i.func(1);
		i.proc(2);

		Verify(mock[&SomeInterface::func]);
		Verify(mock[&SomeInterface::proc]);

		i.func(1);
		i.proc(2);

		Verify(mock[&SomeInterface::func]);
		Verify(mock[&SomeInterface::proc]);
	}

	void verify_method_was_called_exactly_once() {
		Mock<SomeInterface> mock;

		ASSERT_THROW(Verify(mock[&SomeInterface::func]).Once(), mock4cpp::MethodCallVerificationException);
		ASSERT_THROW(Verify(mock[&SomeInterface::proc]).Once(), mock4cpp::MethodCallVerificationException);

		Stub(mock[&SomeInterface::func], mock[&SomeInterface::proc]);
		SomeInterface &i = mock.get();

		ASSERT_THROW(Verify(mock[&SomeInterface::func]).Once(), mock4cpp::MethodCallVerificationException);
		ASSERT_THROW(Verify(mock[&SomeInterface::proc]).Once(), mock4cpp::MethodCallVerificationException);

		i.func(1);
		i.proc(1);

		Verify(mock[&SomeInterface::func]).Once();
		Verify(mock[&SomeInterface::proc]).Once();

		i.func(1);
		i.proc(1);

		ASSERT_THROW(Verify(mock[&SomeInterface::func]).Once(), mock4cpp::MethodCallVerificationException);
		ASSERT_THROW(Verify(mock[&SomeInterface::proc]).Once(), mock4cpp::MethodCallVerificationException);
	}

	void verify_method_was_never_called() {
		Mock<SomeInterface> mock;

		Verify(mock[&SomeInterface::func]).Never();
		Verify(mock[&SomeInterface::proc]).Never();

		Stub(mock[&SomeInterface::func], mock[&SomeInterface::proc]);
		SomeInterface &i = mock.get();

		Verify(mock[&SomeInterface::func]).Never();
		Verify(mock[&SomeInterface::proc]).Never();

		i.func(1);
		i.proc(1);

		ASSERT_THROW(Verify(mock[&SomeInterface::func]).Never(), mock4cpp::MethodCallVerificationException);
		ASSERT_THROW(Verify(mock[&SomeInterface::proc]).Never(), mock4cpp::MethodCallVerificationException);
	}

	void verify_method_was_called_exactly_x_times() {
		Mock<SomeInterface> mock;

		ASSERT_THROW(Verify(mock[&SomeInterface::func]).Times(2), mock4cpp::MethodCallVerificationException);
		ASSERT_THROW(Verify(mock[&SomeInterface::proc]).Times(2), mock4cpp::MethodCallVerificationException);

		Stub(mock[&SomeInterface::func], mock[&SomeInterface::proc]);
		SomeInterface &i = mock.get();

		ASSERT_THROW(Verify(mock[&SomeInterface::func]).Times(2), mock4cpp::MethodCallVerificationException);
		ASSERT_THROW(Verify(mock[&SomeInterface::proc]).Times(2), mock4cpp::MethodCallVerificationException);

		i.func(1);
		i.func(1);
		i.proc(1);
		i.proc(1);

		Verify(mock[&SomeInterface::func]).Times(2);
		Verify(mock[&SomeInterface::proc]).Times(2);

		i.func(1);
		i.proc(1);

		ASSERT_THROW(Verify(mock[&SomeInterface::func]).Times(2), mock4cpp::MethodCallVerificationException);
		ASSERT_THROW(Verify(mock[&SomeInterface::proc]).Times(2), mock4cpp::MethodCallVerificationException);
	}

	void should_throw_IllegalArgumentException_on_negative_times_argument() {
		Mock<SomeInterface> mock;
		ASSERT_THROW(Verify(mock[&SomeInterface::func]).Times(-1), mock4cpp::IllegalArgumentException);
		ASSERT_THROW(Verify(mock[&SomeInterface::proc]).Times(-1), mock4cpp::IllegalArgumentException);
	}

	void verify_with_filter() {
		Mock<SomeInterface> mock;
		Stub(mock[&SomeInterface::func], mock[&SomeInterface::proc]);
		SomeInterface &i = mock.get();
		i.func(1);
		Verify(mock[&SomeInterface::func].Using(1));
		ASSERT_THROW(Verify(mock[&SomeInterface::func].Using(2)), mock4cpp::MethodCallVerificationException);
	}

	void verify_concatenated_sequence() {
		Mock<SomeInterface> mock;
		Stub(mock[&SomeInterface::func], mock[&SomeInterface::proc]);
		SomeInterface &i = mock.get();

		i.func(1);
		i.func(2);
		i.func(3);
		i.func(4);

		Verify(mock[&SomeInterface::func].Using(1) + mock[&SomeInterface::func].Using(2)).Once();
		Verify(mock[&SomeInterface::func].Using(2) + mock[&SomeInterface::func].Using(3)).AtLeastOnce();
		Verify(mock[&SomeInterface::func].Using(3) + mock[&SomeInterface::func].Using(4)).Once();
		Verify(mock[&SomeInterface::func] + mock[&SomeInterface::func]).Twice();
		Verify(mock[&SomeInterface::func].Using(1) + mock[&SomeInterface::func].Using(3)).Never();

		ASSERT_THROW(Verify(mock[&SomeInterface::func].Using(1) + mock[&SomeInterface::func].Using(3)),mock4cpp::MethodCallVerificationException);
	}

	void verify_repeated_sequence() {
		Mock<SomeInterface> mock;
		Stub(mock[&SomeInterface::func], mock[&SomeInterface::proc]);
		SomeInterface &i = mock.get();

		i.func(1);
		i.func(2);
		i.func(3);
		i.func(1);
		i.func(2);
		i.func(3);

		Verify(mock[&SomeInterface::func] * 1).Times(6);
		Verify(mock[&SomeInterface::func] * 2).Times(3);
		Verify(mock[&SomeInterface::func] * 3).Times(2);
		Verify(mock[&SomeInterface::func] * 4).Times(1);
		Verify(mock[&SomeInterface::func] * 5).Times(1);
		Verify(mock[&SomeInterface::func] * 6).Times(1);

		Verify(mock[&SomeInterface::func].Using(1) + mock[&SomeInterface::func].Using(2) +mock[&SomeInterface::func].Using(3)).Twice();
		Verify((mock[&SomeInterface::func].Using(1) + mock[&SomeInterface::func].Using(2) +mock[&SomeInterface::func].Using(3))*2).Once();
		Verify(mock[&SomeInterface::func].Using(1) * 2).Never();

		ASSERT_THROW(Verify(mock[&SomeInterface::func].Using(1) * 2),mock4cpp::MethodCallVerificationException);
	}
//
} __BasicVerification;
