/*
 * Public interface of libqemu-system-*.so built with -Dqenix=true
 *
 * Copyright (c) 2026 Matthew Lee
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef QENIX_H
#define QENIX_H

/*
 * Called with the exit status when QEMU terminates, right before the
 * process exits with _exit().  Runs on whichever thread called exit().
 */
typedef void (*QenixExitHook)(int status);

/*
 * Set the hook called when QEMU terminates.  Must be called before
 * qenix_qemu_main().
 */
void qenix_set_exit_hook(QenixExitHook hook);

/*
 * QEMU's main(): parses @argv, then runs the main loop on the calling
 * thread.  Never returns; QEMU terminates the whole process when it exits.
 * May be called only once per process.
 */
int qenix_qemu_main(int argc, char **argv);

#endif /* QENIX_H */
