// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Protocal.proto

#include "Protocal.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

PROTOBUF_CONSTEXPR PBindName::PBindName(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.name_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct PBindNameDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PBindNameDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PBindNameDefaultTypeInternal() {}
  union {
    PBindName _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PBindNameDefaultTypeInternal _PBindName_default_instance_;
PROTOBUF_CONSTEXPR PChat::PChat(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.information_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct PChatDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PChatDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PChatDefaultTypeInternal() {}
  union {
    PChat _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PChatDefaultTypeInternal _PChat_default_instance_;
PROTOBUF_CONSTEXPR PRoomInformation::PRoomInformation(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.name_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.information_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct PRoomInformationDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PRoomInformationDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PRoomInformationDefaultTypeInternal() {}
  union {
    PRoomInformation _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PRoomInformationDefaultTypeInternal _PRoomInformation_default_instance_;
static ::_pb::Metadata file_level_metadata_Protocal_2eproto[3];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_Protocal_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_Protocal_2eproto = nullptr;

const uint32_t TableStruct_Protocal_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::PBindName, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::PBindName, _impl_.name_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::PChat, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::PChat, _impl_.information_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::PRoomInformation, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::PRoomInformation, _impl_.name_),
  PROTOBUF_FIELD_OFFSET(::PRoomInformation, _impl_.information_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::PBindName)},
  { 7, -1, -1, sizeof(::PChat)},
  { 14, -1, -1, sizeof(::PRoomInformation)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::_PBindName_default_instance_._instance,
  &::_PChat_default_instance_._instance,
  &::_PRoomInformation_default_instance_._instance,
};

const char descriptor_table_protodef_Protocal_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016Protocal.proto\"\031\n\tPBindName\022\014\n\004name\030\001 "
  "\001(\t\"\034\n\005PChat\022\023\n\013information\030\001 \001(\t\"5\n\020PRo"
  "omInformation\022\014\n\004name\030\001 \001(\t\022\023\n\013informati"
  "on\030\002 \001(\tb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_Protocal_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_Protocal_2eproto = {
    false, false, 136, descriptor_table_protodef_Protocal_2eproto,
    "Protocal.proto",
    &descriptor_table_Protocal_2eproto_once, nullptr, 0, 3,
    schemas, file_default_instances, TableStruct_Protocal_2eproto::offsets,
    file_level_metadata_Protocal_2eproto, file_level_enum_descriptors_Protocal_2eproto,
    file_level_service_descriptors_Protocal_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_Protocal_2eproto_getter() {
  return &descriptor_table_Protocal_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_Protocal_2eproto(&descriptor_table_Protocal_2eproto);

// ===================================================================

class PBindName::_Internal {
 public:
};

PBindName::PBindName(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:PBindName)
}
PBindName::PBindName(const PBindName& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  new (&_impl_) Impl_{
      decltype(_impl_.name_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_name().empty()) {
    _impl_.name_.Set(from._internal_name(), 
      GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:PBindName)
}

inline void PBindName::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.name_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

PBindName::~PBindName() {
  // @@protoc_insertion_point(destructor:PBindName)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void PBindName::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.name_.Destroy();
}

void PBindName::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void PBindName::Clear() {
// @@protoc_insertion_point(message_clear_start:PBindName)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.name_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PBindName::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string name = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_name();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "PBindName.name"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* PBindName::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:PBindName)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string name = 1;
  if (!this->_internal_name().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "PBindName.name");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_name(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PBindName)
  return target;
}

size_t PBindName::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PBindName)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string name = 1;
  if (!this->_internal_name().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData PBindName::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    PBindName::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*PBindName::GetClassData() const { return &_class_data_; }

void PBindName::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<PBindName *>(to)->MergeFrom(
      static_cast<const PBindName &>(from));
}


void PBindName::MergeFrom(const PBindName& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PBindName)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_name().empty()) {
    _internal_set_name(from._internal_name());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void PBindName::CopyFrom(const PBindName& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PBindName)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PBindName::IsInitialized() const {
  return true;
}

void PBindName::InternalSwap(PBindName* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.name_, lhs_arena,
      &other->_impl_.name_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata PBindName::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Protocal_2eproto_getter, &descriptor_table_Protocal_2eproto_once,
      file_level_metadata_Protocal_2eproto[0]);
}

// ===================================================================

class PChat::_Internal {
 public:
};

PChat::PChat(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:PChat)
}
PChat::PChat(const PChat& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  new (&_impl_) Impl_{
      decltype(_impl_.information_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.information_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.information_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_information().empty()) {
    _impl_.information_.Set(from._internal_information(), 
      GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:PChat)
}

inline void PChat::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.information_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.information_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.information_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

PChat::~PChat() {
  // @@protoc_insertion_point(destructor:PChat)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void PChat::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.information_.Destroy();
}

void PChat::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void PChat::Clear() {
// @@protoc_insertion_point(message_clear_start:PChat)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.information_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PChat::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string information = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_information();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "PChat.information"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* PChat::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:PChat)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string information = 1;
  if (!this->_internal_information().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_information().data(), static_cast<int>(this->_internal_information().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "PChat.information");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_information(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PChat)
  return target;
}

size_t PChat::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PChat)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string information = 1;
  if (!this->_internal_information().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_information());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData PChat::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    PChat::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*PChat::GetClassData() const { return &_class_data_; }

void PChat::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<PChat *>(to)->MergeFrom(
      static_cast<const PChat &>(from));
}


void PChat::MergeFrom(const PChat& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PChat)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_information().empty()) {
    _internal_set_information(from._internal_information());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void PChat::CopyFrom(const PChat& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PChat)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PChat::IsInitialized() const {
  return true;
}

void PChat::InternalSwap(PChat* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.information_, lhs_arena,
      &other->_impl_.information_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata PChat::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Protocal_2eproto_getter, &descriptor_table_Protocal_2eproto_once,
      file_level_metadata_Protocal_2eproto[1]);
}

// ===================================================================

class PRoomInformation::_Internal {
 public:
};

PRoomInformation::PRoomInformation(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:PRoomInformation)
}
PRoomInformation::PRoomInformation(const PRoomInformation& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  new (&_impl_) Impl_{
      decltype(_impl_.name_){}
    , decltype(_impl_.information_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_name().empty()) {
    _impl_.name_.Set(from._internal_name(), 
      GetArenaForAllocation());
  }
  _impl_.information_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.information_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_information().empty()) {
    _impl_.information_.Set(from._internal_information(), 
      GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:PRoomInformation)
}

inline void PRoomInformation::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.name_){}
    , decltype(_impl_.information_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.information_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.information_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

PRoomInformation::~PRoomInformation() {
  // @@protoc_insertion_point(destructor:PRoomInformation)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void PRoomInformation::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.name_.Destroy();
  _impl_.information_.Destroy();
}

void PRoomInformation::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void PRoomInformation::Clear() {
// @@protoc_insertion_point(message_clear_start:PRoomInformation)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.name_.ClearToEmpty();
  _impl_.information_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PRoomInformation::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string name = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_name();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "PRoomInformation.name"));
        } else
          goto handle_unusual;
        continue;
      // string information = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_information();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "PRoomInformation.information"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* PRoomInformation::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:PRoomInformation)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string name = 1;
  if (!this->_internal_name().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "PRoomInformation.name");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_name(), target);
  }

  // string information = 2;
  if (!this->_internal_information().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_information().data(), static_cast<int>(this->_internal_information().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "PRoomInformation.information");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_information(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PRoomInformation)
  return target;
}

size_t PRoomInformation::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PRoomInformation)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string name = 1;
  if (!this->_internal_name().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());
  }

  // string information = 2;
  if (!this->_internal_information().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_information());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData PRoomInformation::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    PRoomInformation::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*PRoomInformation::GetClassData() const { return &_class_data_; }

void PRoomInformation::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<PRoomInformation *>(to)->MergeFrom(
      static_cast<const PRoomInformation &>(from));
}


void PRoomInformation::MergeFrom(const PRoomInformation& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PRoomInformation)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_name().empty()) {
    _internal_set_name(from._internal_name());
  }
  if (!from._internal_information().empty()) {
    _internal_set_information(from._internal_information());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void PRoomInformation::CopyFrom(const PRoomInformation& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PRoomInformation)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PRoomInformation::IsInitialized() const {
  return true;
}

void PRoomInformation::InternalSwap(PRoomInformation* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.name_, lhs_arena,
      &other->_impl_.name_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.information_, lhs_arena,
      &other->_impl_.information_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata PRoomInformation::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Protocal_2eproto_getter, &descriptor_table_Protocal_2eproto_once,
      file_level_metadata_Protocal_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::PBindName*
Arena::CreateMaybeMessage< ::PBindName >(Arena* arena) {
  return Arena::CreateMessageInternal< ::PBindName >(arena);
}
template<> PROTOBUF_NOINLINE ::PChat*
Arena::CreateMaybeMessage< ::PChat >(Arena* arena) {
  return Arena::CreateMessageInternal< ::PChat >(arena);
}
template<> PROTOBUF_NOINLINE ::PRoomInformation*
Arena::CreateMaybeMessage< ::PRoomInformation >(Arena* arena) {
  return Arena::CreateMessageInternal< ::PRoomInformation >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
