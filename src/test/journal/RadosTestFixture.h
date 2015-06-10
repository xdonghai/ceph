// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab

#include "test/librados/test.h"
#include "common/Mutex.h"
#include "common/Timer.h"
#include "cls/journal/cls_journal_types.h"
#include "gtest/gtest.h"

class RadosTestFixture : public ::testing::Test {
public:
  static void SetUpTestCase();
  static void TearDownTestCase();

  static std::string get_temp_oid();

  RadosTestFixture();
  virtual void SetUp();
  virtual void TearDown();

  int create(const std::string &oid, uint8_t order, uint8_t splay_width);
  int append(const std::string &oid, const bufferlist &bl);

  int client_register(const std::string &oid, const std::string &id,
                      const std::string &description);
  int client_commit(const std::string &oid, const std::string &id,
                    const cls::journal::ObjectSetPosition &commit_position);

  bufferlist create_payload(const std::string &payload);

  static std::string _pool_name;
  static librados::Rados _rados;
  static uint64_t _oid_number;

  librados::IoCtx m_ioctx;

  Mutex m_timer_lock;
  SafeTimer *m_timer;
};
