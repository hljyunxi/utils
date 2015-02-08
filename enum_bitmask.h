#define DEFINE_BITMASK_ENUM_OPERATIONS(Type) \
inline Type EnumBitMaskOr(Type lhs, Type rhs) {return lhs | rhs;}\
inline Type EnumBitMaskAnd(Type lhs, Type rhs){return lhs & rhs;}
