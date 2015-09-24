DIST_SUBDIRS = secp256k1
AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS)


if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(CXXFLAGS) $(CPPFLAGS) -D__STDC_LIMIT_MACROS"
endif

PHTEVENCOIN_CONFIG_INCLUDES=-I$(builddir)/config
PHTEVENCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

PHTEVENCOIN_INCLUDES += -I$(srcdir)/secp256k1/include

LIBPHTEVENCOIN_SERVER=libphtevencoin_server.a
LIBPHTEVENCOIN_WALLET=libphtevencoin_wallet.a
LIBPHTEVENCOIN_COMMON=libphtevencoin_common.a
LIBPHTEVENCOIN_CLI=libphtevencoin_cli.a
LIBPHTEVENCOIN_UTIL=libphtevencoin_util.a
LIBPHTEVENCOIN_CRYPTO=crypto/libphtevencoin_crypto.a
LIBPHTEVENCOIN_UNIVALUE=univalue/libphtevencoin_univalue.a
LIBPHTEVENCOINQT=qt/libphtevencoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libphtevencoin_crypto.a \
  libphtevencoin_util.a \
  libphtevencoin_common.a \
  univalue/libphtevencoin_univalue.a \
  libphtevencoin_server.a \
  libphtevencoin_cli.a
if ENABLE_WALLET
PHTEVENCOIN_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libphtevencoin_wallet.a
endif
if ENABLE_ZMQ
EXTRA_LIBRARIES += libphtevencoin_zmq.a
endif

if BUILD_PHTEVENCOIN_LIBS
lib_LTLIBRARIES = libphtevencoinconsensus.la
LIBPHTEVENCOIN_CONSENSUS=libphtevencoinconsensus.la
else
LIBPHTEVENCOIN_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =

if BUILD_PHTEVENCOIND
  bin_PROGRAMS += phtevencoind
endif

if BUILD_PHTEVENCOIN_UTILS
  bin_PROGRAMS += phtevencoin-cli phtevencoin-tx
endif

.PHONY: FORCE
# phtevencoin core #
PHTEVENCOIN_CORE_H = \
  addrman.h \
  alert.h \
  amount.h \
  arith_uint256.h \
  base58.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/params.h \
  consensus/validation.h \
  core_io.h \
  core_memusage.h \
  eccryptoverify.h \
  ecwrapper.h \
  hash.h \
  httprpc.h \
  httpserver.h \
  init.h \
  key.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  mruset.h \
  net.h \
  netbase.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  pow.h \
  primitives/block.h \
  primitives/transaction.h \
  protocol.h \
  pubkey.h \
  random.h \
  reverselock.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  scheduler.h \
  script/interpreter.h \
  script/script.h \
  script/script_error.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  serialize.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/pagelocker.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utilstrencodings.h \
  utiltime.h \
  validationinterface.h \
  version.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/wallet.h \
  wallet/wallet_ismine.h \
  wallet/walletdb.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libphtevencoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between phtevencoind and phtevencoin-qt
libphtevencoin_server_a_CPPFLAGS = $(PHTEVENCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libphtevencoin_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  rest.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  txdb.cpp \
  txmempool.cpp \
  validationinterface.cpp \
  $(PHTEVENCOIN_CORE_H)

if ENABLE_ZMQ
LIBPHTEVENCOIN_ZMQ=libphtevencoin_zmq.a

libphtevencoin_zmq_a_CPPFLAGS = $(PHTEVENCOIN_INCLUDES)
libphtevencoin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between phtevencoind and phtevencoin-qt, but only linked
# when wallet enabled
libphtevencoin_wallet_a_CPPFLAGS = $(PHTEVENCOIN_INCLUDES)
libphtevencoin_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/wallet_ismine.cpp \
  wallet/walletdb.cpp \
  $(PHTEVENCOIN_CORE_H)

# crypto primitives library
crypto_libphtevencoin_crypto_a_CPPFLAGS = $(PHTEVENCOIN_CONFIG_INCLUDES)
crypto_libphtevencoin_crypto_a_SOURCES = \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

# univalue JSON library
univalue_libphtevencoin_univalue_a_SOURCES = \
  univalue/univalue.cpp \
  univalue/univalue.h \
  univalue/univalue_escapes.h \
  univalue/univalue_read.cpp \
  univalue/univalue_write.cpp

# common: shared between phtevencoind, and phtevencoin-qt and non-server tools
libphtevencoin_common_a_CPPFLAGS = $(PHTEVENCOIN_INCLUDES)
libphtevencoin_common_a_SOURCES = \
  amount.cpp \
  arith_uint256.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  protocol.cpp \
  pubkey.cpp \
  scheduler.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/script_error.cpp \
  script/sign.cpp \
  script/standard.cpp \
  $(PHTEVENCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libphtevencoin_util_a_CPPFLAGS = $(PHTEVENCOIN_INCLUDES)
libphtevencoin_util_a_SOURCES = \
  support/pagelocker.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpcprotocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(PHTEVENCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libphtevencoin_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between phtevencoin-cli and phtevencoin-qt
libphtevencoin_cli_a_CPPFLAGS = $(PHTEVENCOIN_INCLUDES)
libphtevencoin_cli_a_SOURCES = \
  rpcclient.cpp \
  $(PHTEVENCOIN_CORE_H)

nodist_libphtevencoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# phtevencoind binary #
phtevencoind_SOURCES = phtevencoind.cpp
phtevencoind_CPPFLAGS = $(PHTEVENCOIN_INCLUDES)
phtevencoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
phtevencoind_SOURCES += phtevencoind-res.rc
endif

phtevencoind_LDADD = \
  $(LIBPHTEVENCOIN_SERVER) \
  $(LIBPHTEVENCOIN_COMMON) \
  $(LIBPHTEVENCOIN_UNIVALUE) \
  $(LIBPHTEVENCOIN_UTIL) \
  $(LIBPHTEVENCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_ZMQ
phtevencoind_LDADD += $(LIBPHTEVENCOIN_ZMQ) $(ZMQ_LIBS)
endif

if ENABLE_WALLET
phtevencoind_LDADD += libphtevencoin_wallet.a
endif

phtevencoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS)

# phtevencoin-cli binary #
phtevencoin_cli_SOURCES = phtevencoin-cli.cpp
phtevencoin_cli_CPPFLAGS = $(PHTEVENCOIN_INCLUDES) $(EVENT_CFLAGS)
phtevencoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
phtevencoin_cli_SOURCES += phtevencoin-cli-res.rc
endif

phtevencoin_cli_LDADD = \
  $(LIBPHTEVENCOIN_CLI) \
  $(LIBPHTEVENCOIN_UNIVALUE) \
  $(LIBPHTEVENCOIN_UTIL) \
  $(LIBSECP256K1)

phtevencoin_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# phtevencoin-tx binary #
phtevencoin_tx_SOURCES = phtevencoin-tx.cpp
phtevencoin_tx_CPPFLAGS = $(PHTEVENCOIN_INCLUDES)
phtevencoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
phtevencoin_tx_SOURCES += phtevencoin-tx-res.rc
endif

phtevencoin_tx_LDADD = \
  $(LIBPHTEVENCOIN_UNIVALUE) \
  $(LIBPHTEVENCOIN_COMMON) \
  $(LIBPHTEVENCOIN_UTIL) \
  $(LIBPHTEVENCOIN_CRYPTO) \
  $(LIBSECP256K1)

phtevencoin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# phtevencoinconsensus library #
if BUILD_PHTEVENCOIN_LIBS
include_HEADERS = script/phtevencoinconsensus.h
libphtevencoinconsensus_la_SOURCES = \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  primitives/transaction.cpp \
  pubkey.cpp \
  script/phtevencoinconsensus.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libphtevencoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libphtevencoinconsensus_la_LDFLAGS = -no-undefined $(RELDFLAGS)
libphtevencoinconsensus_la_LIBADD = $(CRYPTO_LIBS)
libphtevencoinconsensus_la_CPPFLAGS = $(CRYPTO_CFLAGS) -I$(builddir)/obj -DBUILD_PHTEVENCOIN_INTERNAL

endif
#

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(CXXFLAGS)  -c -o $@ $<

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
