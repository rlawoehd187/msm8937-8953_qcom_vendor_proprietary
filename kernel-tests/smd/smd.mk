#sources and intermediate files are separated
vpath %.c $(SRCDIR)/smd

SMDTEST_CFLAGS := $(CFLAGS)
SMDTEST_CFLAGS += $(QCT_CFLAGS)

SMDTEST_CPPFLAGS := $(CPPFLAGS)
SMDTEST_CPPFLAGS += $(QCT_CPPFLAGS)

SMDLDLIBS := $(LDLIBS)
SMDLDLIBS += -lpthread -lrt

SMEM_LOG_TEST := smem_log_test
SMEM_LOG_SRCLIST := smem_log_test.c

SMD_TTY_LOOPBACK_TEST := smd_tty_loopback_test
SMD_TTY_LOOPBACK_SRCLIST := smd_tty_loopback_test.c

SMD_PKT_LOOPBACK_TEST := smd_pkt_loopback_test
SMD_PKT_LOOPBACK_SRCLIST := smd_pkt_loopback_test.c

all: $(SMEM_LOG_TEST) $(SMD_TTY_LOOPBACK_TEST) $(SMD_PKT_LOOPBACK_TEST)

$(SMEM_LOG_TEST): $(SMEM_LOG_SRCLIST)
	$(CC) $(SMDTEST_CFLAGS) $(SMDTEST_CPPFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(SMD_TTY_LOOPBACK_TEST): $(SMD_TTY_LOOPBACK_SRCLIST)
	$(CC) $(SMDTEST_CFLAGS) $(SMDTEST_CPPFLAGS) $(LDFLAGS) -o $@ $^ $(SMDLDLIBS)

$(SMD_PKT_LOOPBACK_TEST): $(SMD_PKT_LOOPBACK_SRCLIST)
	$(CC) $(SMDTEST_CFLAGS) $(SMDTEST_CPPFLAGS) $(LDFLAGS) -o $@ $^ $(SMDLDLIBS)
