/*
 * qenix: process exit for the system emulator shared library
 *
 * Copyright (c) 2026 Matthew Lee
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "qemu/osdep.h"
#include "qenix.h"

static QenixExitHook exit_hook;

void qenix_set_exit_hook(QenixExitHook hook)
{
    exit_hook = hook;
}

G_NORETURN void __wrap_exit(int status);

/*
 * Every exit() in the library is linked to this function with
 * -Wl,--wrap=exit.
 *
 * The library runs inside an Android app process.  exit() would run the
 * static destructors and atexit handlers of the whole process, including
 * the ones of ART, while ART and QEMU threads are still running; that
 * crashes and shows an "app has stopped" dialog.  _exit() terminates the
 * process without running any of them.
 */
void __wrap_exit(int status)
{
    fflush(stdout);
    fflush(stderr);
    if (exit_hook) {
        exit_hook(status);
    }
    _exit(status);
}
