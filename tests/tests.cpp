#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#define BOOST_TEST_MODULE typist_test_module
#pragma clang diagnostic pop

#include <boost/test/unit_test.hpp>
#include <boost/type_index.hpp>
#include <typist/typist.hpp>

using namespace std;
using namespace typist;
using namespace boost::unit_test_framework;
using namespace boost::typeindex;

//region TestTypes
using BasicType                      = int;
using ConstType                      = int const;
using lValueRef                      = int &;
using lValueRefToConst               = int const &;
using rValueRef                      = int &&;
using rValueRefConst                 = int const &&;
using Pointer                        = int *;
using PointerToConst                 = int const *;
using ConstPointer                   = int *const;
using ConstPointerToConst            = int const *const;
using lValueRefToPointer             = int *&;
using lValueRefToPointerToConst      = int const *&;
using lValueRefToConstPointer        = int *const &;
using lValueRefToConstPointerToConst = int const *const &;
using rValueRefToPointer             = int *&&;
using rValueRefToPointerToConst      = int const *&&;
using rValueRefToConstPointer        = int *const &&;
using rValueRefToConstPointerToConst = int const *const &&;
//endregion

//region stripAllTests
BOOST_AUTO_TEST_SUITE( stripAllTests )  // NOLINT

    BOOST_AUTO_TEST_CASE( SimpleCases ) { // NOLINT
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<ConstType> )).value );
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<lValueRef> )).value );
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<lValueRefToConst> )).value );
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<rValueRef> )).value );
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<rValueRef> )).value );
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<rValueRefConst> )).value );
    }

    BOOST_AUTO_TEST_CASE( Pointers ) { // NOLINT
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<Pointer> )).value );
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<PointerToConst> )).value );
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<ConstPointer> )).value );
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<ConstPointerToConst> )).value );
    }

    BOOST_AUTO_TEST_CASE ( lRefToPointer ) { // NOLINT
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<lValueRefToPointer> )).value );
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<lValueRefToPointerToConst> )).value );
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<lValueRefToConstPointer> )).value );
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<lValueRefToConstPointerToConst> )).value );
    }

    BOOST_AUTO_TEST_CASE( rRefToPointer ) { // NOLINT
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<rValueRefToPointer> )).value );
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<rValueRefToPointerToConst> )).value );
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<rValueRefToConstPointer> )).value );
        BOOST_TEST_CHECK(( type_c<BasicType> == stripAll( type_c<rValueRefToConstPointerToConst> )).value );
    }

BOOST_AUTO_TEST_SUITE_END() // NOLINT
//endregion

//region manipulateTests
BOOST_AUTO_TEST_SUITE( manipulateTests ) // NOLINT
    using namespace Outputs;
    auto basic = type_c<BasicType>;

    BOOST_AUTO_TEST_CASE( REGULAR_TEST ) { // NOLINT
        BOOST_TEST_CHECK(( basic == manipulate( basic, REGULAR )));
    }

    BOOST_AUTO_TEST_CASE( CONSTANT_TEST ) { // NOLINT
        BOOST_TEST_CHECK(( type_c<ConstType> == manipulate( basic, CONSTANT )));
    }

    BOOST_AUTO_TEST_CASE( REFERENCE_TEST ) { // NOLINT
        BOOST_TEST_CHECK(( type_c<lValueRef> == manipulate( basic, REFERENCE )));
    }

    BOOST_AUTO_TEST_CASE( CONSTANT_REFERENCE_TEST ) { // NOLINT
        auto manipulated = manipulate( basic, CONSTANT_REFERENCE );
        BOOST_TEST_CHECK(( type_c<lValueRefToConst> == manipulated ),
                         type_id_with_cvr<decltype( manipulated )::type>().pretty_name());
    }

    BOOST_AUTO_TEST_CASE( R_VALUE_TEST ) { // NOLINT
        BOOST_TEST_CHECK(( type_c<rValueRef> == manipulate( basic, R_VALUE )));
    }

    BOOST_AUTO_TEST_CASE( CONSTANT_R_VALUE_TEST ) { // NOLINT
        auto manipulated = manipulate( basic, CONSTANT_R_VALUE );
        BOOST_TEST_CHECK(( type_c<rValueRefConst> == manipulated ),
                         type_id_with_cvr<decltype( manipulated )::type>().pretty_name());
    }

    BOOST_AUTO_TEST_CASE( POINTER_TEST ) { // NOLINT
        auto manipulated = manipulate( basic, POINTER );
        BOOST_TEST_CHECK(( type_c<Pointer> == manipulated ),
                         type_id_with_cvr<decltype( manipulated )::type>().pretty_name());
    }

    BOOST_AUTO_TEST_CASE( POINTER_TO_CONSTANT_TEST ) { // NOLINT
        auto manipulated = manipulate( basic, POINTER_TO_CONSTANT );
        BOOST_TEST_CHECK(( type_c<PointerToConst> == manipulated ),
                         type_id_with_cvr<decltype( manipulated )::type>().pretty_name());
    }

    BOOST_AUTO_TEST_CASE( CONSTANT_POINTER_TEST ) { // NOLINT
        auto manipulated = manipulate( basic, CONSTANT_POINTER );
        BOOST_TEST_CHECK(( type_c<ConstPointer> == manipulated ),
                         type_id_with_cvr<decltype( manipulated )::type>().pretty_name());
    }

    BOOST_AUTO_TEST_CASE( CONSTANT_POINTER_TO_CONSTANT_TEST ) { // NOLINT
        auto manipulated = manipulate( basic, CONSTANT_POINTER_TO_CONSTANT );
        BOOST_TEST_CHECK(( type_c<ConstPointerToConst> == manipulated ),
                         type_id_with_cvr<decltype( manipulated )::type>().pretty_name());
    }

    BOOST_AUTO_TEST_CASE( REFERENCE_TO_POINTER_TEST ) { // NOLINT
        auto manipulated = manipulate( basic, REFERENCE_TO_POINTER );
        BOOST_TEST_CHECK(( type_c<lValueRefToPointer> == manipulated ),
                         type_id_with_cvr<decltype( manipulated )::type>().pretty_name());
    }

    BOOST_AUTO_TEST_CASE( REFERENCE_TO_POINTER_TO_CONSTANT_TEST ) { // NOLINT
        auto manipulated = manipulate( basic, REFERENCE_TO_POINTER_TO_CONSTANT );
        BOOST_TEST_CHECK(( type_c<lValueRefToPointerToConst> == manipulated ),
                         type_id_with_cvr<decltype( manipulated )::type>().pretty_name());
    }

    BOOST_AUTO_TEST_CASE( REFERENCE_TO_CONSTANT_POINTER_TEST ) { // NOLINT
        auto manipulated = manipulate( basic, REFERENCE_TO_CONSTANT_POINTER );
        BOOST_TEST_CHECK(( type_c<lValueRefToConstPointer> == manipulated ),
                         type_id_with_cvr<decltype( manipulated )::type>().pretty_name());
    }

    BOOST_AUTO_TEST_CASE( REFERENCE_TO_CONSTANT_POINTER_TO_CONSTANT_TEST ) { // NOLINT
        auto manipulated = manipulate( basic, REFERENCE_TO_CONSTANT_POINTER_TO_CONSTANT );
        BOOST_TEST_CHECK(( type_c<lValueRefToConstPointerToConst> == manipulated ),
                         type_id_with_cvr<decltype( manipulated )::type>().pretty_name());
    }

    BOOST_AUTO_TEST_CASE( R_VALUE_POINTER_TEST ) {
        auto manipulated = manipulate( basic, R_VALUE_POINTER );
        BOOST_TEST_CHECK(( type_c<rValueRefToPointer> == manipulated ),
                         type_id_with_cvr<decltype( manipulated )::type>().pretty_name());
    }

    BOOST_AUTO_TEST_CASE( R_VALUE_POINTER_TO_CONSTANT_TEST ) {
        auto manipulated = manipulate( basic, R_VALUE_POINTER_TO_CONSTANT );
        BOOST_TEST_CHECK(( type_c<rValueRefToPointerToConst> == manipulated ),
                         type_id_with_cvr<decltype( manipulated )::type>().pretty_name());
    }

    BOOST_AUTO_TEST_CASE( R_VALUE_CONSTANT_POINTER_TEST ) {
        auto manipulated = manipulate( basic, R_VALUE_CONSTANT_POINTER );
        BOOST_TEST_CHECK(( type_c<rValueRefToConstPointer> == manipulated ),
                         type_id_with_cvr<decltype( manipulated )::type>().pretty_name());
    }

    BOOST_AUTO_TEST_CASE( R_VALUE_CONSTANT_POINTER_TO_CONSTANT_TEST ) {
        auto manipulated = manipulate( basic, R_VALUE_CONSTANT_POINTER_TO_CONSTANT );
        BOOST_TEST_CHECK(( type_c<rValueRefToConstPointerToConst> == manipulated ),
                         type_id_with_cvr<decltype( manipulated )::type>().pretty_name());
    }

BOOST_AUTO_TEST_SUITE_END() // NOLINT
//endregion
