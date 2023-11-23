/**** db.h ****
 *
 *  Copyright (c) 2023 Shoggoth Systems - https://shoggoth.systems
 *
 * Part of the ShogDB database, under the MIT License.
 * See LICENCE file for license information.
 * SPDX-License-Identifier: MIT
 *
 ****/

#ifndef SHOGDB_H
#define SHOGDB_H

#include "../../include/cjson.h"
#include "../../include/sonic.h"
#include "../hashmap/hashmap.h"
#include "../lib/lib.h"

#include <netlibc.h>
#include <netlibc/error.h>
#include <pthread.h>

typedef struct {
  char *host;
  u16 port;
} network_config_t;

typedef struct {
  char *path;
  u64 interval;
} save_config_t;

typedef struct {
  network_config_t network;
  save_config_t save;
} db_config_t;

typedef struct {
  hashmap_t *hashmap;
  db_config_t *config;
  bool should_exit;
  bool server_started;
  bool saved;
  sonic_server_t *http_server;
} db_ctx_t;

result_t db_get_value(db_ctx_t *ctx, char *key);

void db_add_json_value(db_ctx_t *ctx, char *key, cJSON *val);

result_t start_db(db_ctx_t *ctx);

db_ctx_t *new_db(db_config_t *config);

void free_db(db_ctx_t *ctx);

void db_save_data(db_ctx_t *ctx);

result_t db_delete_value(db_ctx_t *ctx, char *key);

#endif