/**
 * \file genshellcfg.h
 *
 * Generic shell configurations, copy this file into your project and modify as needed
 */

#ifndef GENERIC_SHELL_CONF_H
#define GENERIC_SHELL_CONF_H

/**
 * Generic shell start message to print on system startup
 */
#ifndef GEN_SHELL_START_MSG
#define GEN_SHELL_START_MSG \
	"Project Name\n" \
	"Project Description\n" \
	"~~~~~~~~~~~~~~~~~~~\n"
#endif

/**
 * Generic shell prompt
 */
#ifndef GEN_SHELL_PROMPT
#define GEN_SHELL_PROMPT ">"
#endif

#endif /* GENERIC_SHELL_CONF_H */