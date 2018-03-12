#pragma once

#include <boost/hana.hpp>

namespace typist {
    using boost::hana::type_c;

    namespace Outputs {
        namespace {
            struct REGULAR_t {};
            struct CONSTANT_t {};
            struct REFERENCE_t {};
            struct CONSTANT_REFERENCE_t {};
            struct R_VALUE_t {};
            struct CONSTANT_R_VALUE_t {};
            struct POINTER_t {};
            struct POINTER_TO_CONSTANT_t {};
            struct CONSTANT_POINTER_t {};
            struct CONSTANT_POINTER_TO_CONSTANT_t {};
            struct REFERENCE_TO_POINTER_t {};
            struct REFERENCE_TO_POINTER_TO_CONSTANT_t {};
            struct REFERENCE_TO_CONSTANT_POINTER_t {};
            struct REFERENCE_TO_CONSTANT_POINTER_TO_CONSTANT_t {};
            struct R_VALUE_POINTER_t {};
            struct R_VALUE_POINTER_TO_CONSTANT_t {};
            struct R_VALUE_CONSTANT_POINTER_t {};
            struct R_VALUE_CONSTANT_POINTER_TO_CONSTANT_t {};
        }

        auto const REGULAR                                   = boost::hana::type_c<REGULAR_t>;
        auto const CONSTANT                                  = boost::hana::type_c<CONSTANT_t>;
        auto const REFERENCE                                 = boost::hana::type_c<REFERENCE_t>;
        auto const CONSTANT_REFERENCE                        = boost::hana::type_c<CONSTANT_REFERENCE_t>;
        auto const R_VALUE                                   = boost::hana::type_c<R_VALUE_t>;
        auto const CONSTANT_R_VALUE                          = boost::hana::type_c<CONSTANT_R_VALUE_t>;
        auto const POINTER                                   = boost::hana::type_c<POINTER_t>;
        auto const POINTER_TO_CONSTANT                       = boost::hana::type_c<POINTER_TO_CONSTANT_t>;
        auto const CONSTANT_POINTER                          = boost::hana::type_c<CONSTANT_POINTER_t>;
        auto const CONSTANT_POINTER_TO_CONSTANT              = boost::hana::type_c<CONSTANT_POINTER_TO_CONSTANT_t>;
        auto const REFERENCE_TO_POINTER                      = boost::hana::type_c<REFERENCE_TO_POINTER_t>;
        auto const REFERENCE_TO_POINTER_TO_CONSTANT          = boost::hana::type_c<REFERENCE_TO_POINTER_TO_CONSTANT_t>;
        auto const REFERENCE_TO_CONSTANT_POINTER             = boost::hana::type_c<REFERENCE_TO_CONSTANT_POINTER_t>;
        auto const REFERENCE_TO_CONSTANT_POINTER_TO_CONSTANT =
                           boost::hana::type_c<REFERENCE_TO_CONSTANT_POINTER_TO_CONSTANT_t>;
        auto const R_VALUE_POINTER                           = boost::hana::type_c<R_VALUE_POINTER_t>;
        auto const R_VALUE_POINTER_TO_CONSTANT               = boost::hana::type_c<R_VALUE_POINTER_TO_CONSTANT_t>;
        auto const R_VALUE_CONSTANT_POINTER                  = boost::hana::type_c<R_VALUE_CONSTANT_POINTER_t>;
        auto const R_VALUE_CONSTANT_POINTER_TO_CONSTANT      =
                           boost::hana::type_c<R_VALUE_CONSTANT_POINTER_TO_CONSTANT_t>;
    };

    /**
     * This function takes a type and returns a new type that is stripped of an constant,
     * volatility, reference, and pointer qualifiers
     * @tparam T This is the actual type. It will be deduced automatically, there is no need to provide it
     * @param type Takes a type object
     * @return
     */
    template< typename T >
    constexpr auto stripAll( boost::hana::basic_type<T> const &type ) noexcept {
        auto noCvOuter = boost::hana::traits::remove_cv( type );
        auto noRef     = boost::hana::traits::remove_reference( noCvOuter );
        auto noPointer = boost::hana::traits::remove_pointer( noRef );
        return boost::hana::traits::remove_cv( noPointer );
    }


    /**
     * This function takes a type object and one of the constants from the Outputs namespace
     * It returns a new type object that is manipulated accordingly
     * @tparam T
     * @tparam Output
     * @param type
     * @param output
     * @return
     */
    template< typename T, typename Output >
    constexpr auto manipulate( boost::hana::basic_type<T> const &type, Output const &output ) noexcept {
        using namespace boost::hana;
        using namespace boost::hana::traits;
        using namespace Outputs;
        auto identity = []( basic_type<T> const &type ) { return type; };
        using namespace Outputs;

        auto stripped = stripAll( type );

        auto isRegular              = bool_<REGULAR == output>{};
        auto isConstant             = bool_<CONSTANT == output>{};
        auto isReference            = bool_<REFERENCE == output>{};
        auto isConstantReference    = bool_<CONSTANT_REFERENCE == output>{};
        auto isRValue               = bool_<R_VALUE == output>{};
        auto isConstantRValue       = bool_<CONSTANT_R_VALUE == output>{};
        auto isPointer              = bool_<POINTER == output>{};
        auto isPointerToConstant    = bool_<POINTER_TO_CONSTANT == output>{};
        auto isConstantPointer      = bool_<CONSTANT_POINTER == output>{};
        auto isConstPtrToConst      = bool_<CONSTANT_POINTER_TO_CONSTANT == output>{};
        auto isRefToPtr             = bool_<REFERENCE_TO_POINTER == output>{};
        auto isRefToPtrToConst      = bool_<REFERENCE_TO_POINTER_TO_CONSTANT == output>{};
        auto isRefToConstPtr        = bool_<REFERENCE_TO_CONSTANT_POINTER == output>{};
        auto isRefToConstPtrToConst = bool_<REFERENCE_TO_CONSTANT_POINTER_TO_CONSTANT == output>{};
        auto isRValPtr              = bool_<R_VALUE_POINTER == output>{};
        auto isRValPtrToConst       = bool_<R_VALUE_POINTER_TO_CONSTANT == output>{};
        auto isRValConstPtr         = bool_<R_VALUE_CONSTANT_POINTER == output>{};
        auto isRValConstPtrToConst  = bool_<R_VALUE_CONSTANT_POINTER_TO_CONSTANT == output>{};
        auto manipulator            =
                     if_( isRegular, identity,
                     if_( isConstant, add_const,
                     if_( isReference, add_lvalue_reference,
                     if_( isConstantReference, compose( add_lvalue_reference, add_const ),
                     if_( isRValue, add_rvalue_reference,
                     if_( isConstantRValue, compose( add_rvalue_reference, add_const ),
                     if_( isPointer, add_pointer,
                     if_( isPointerToConstant, compose( add_pointer, add_const ),
                     if_( isConstantPointer, compose( add_const, add_pointer ),
                     if_( isConstPtrToConst, compose( add_const, add_pointer, add_const ),
                     if_( isRefToPtr, compose( add_lvalue_reference, add_pointer ),
                     if_( isRefToPtrToConst, compose( add_lvalue_reference, add_pointer, add_const ),
                     if_( isRefToConstPtr, compose( add_lvalue_reference, add_const, add_pointer ),
                     if_( isRefToConstPtrToConst, compose( add_lvalue_reference, add_const, add_pointer, add_const ),
                     if_( isRValPtr, compose( add_rvalue_reference, add_pointer ),
                     if_( isRValPtrToConst, compose( add_rvalue_reference, add_pointer, add_const ),
                     if_( isRValConstPtr, compose( add_rvalue_reference, add_const, add_pointer ),
                     if_( isRValConstPtrToConst, compose( add_rvalue_reference, add_const, add_pointer, add_const ),
                     nothing ))))))))))))))))));

        BOOST_HANA_CONSTANT_CHECK_MSG( manipulator != nothing, "Invalid output type" );
        return manipulator( stripped );
    };
}