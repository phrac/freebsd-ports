/* friend_requests.c
 *
 * Handle friend requests.
 *
 *  Copyright (C) 2013 Tox project All Rights Reserved.
 *
 *  This file is part of Tox.
 *
 *  Tox is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Tox is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Tox.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "friend_requests.h"
#include "util.h"

/* Try to send a friend request to peer with public_key.
 * data is the data in the request and length is the length.
 *
 *  return -1 if failure.
 *  return  0 if it sent the friend request directly to the friend.
 *  return the number of peers it was routed through if it did not send it directly.
 */
int send_friendrequest(Onion_Client *onion_c, uint8_t *public_key, uint32_t nospam_num, uint8_t *data, uint32_t length)
{
    if (length + sizeof(nospam_num) > MAX_DATA_SIZE)
        return -1;

    uint8_t temp[MAX_DATA_SIZE];
    temp[0] = CRYPTO_PACKET_FRIEND_REQ;
    memcpy(temp + 1, &nospam_num, sizeof(nospam_num));
    memcpy(temp + 1 + sizeof(nospam_num), data, length);

    int friend_num = onion_friend_num(onion_c, public_key);

    if (friend_num == -1)
        return -1;

    int num = send_onion_data(onion_c, friend_num, temp, 1 + sizeof(nospam_num) + length);

    if (num <= 0)
        return -1;

    return num;
}


/* Set and get the nospam variable used to prevent one type of friend request spam. */
void set_nospam(Friend_Requests *fr, uint32_t num)
{
    fr->nospam = num;
}

uint32_t get_nospam(Friend_Requests *fr)
{
    return fr->nospam;
}


/* Set the function that will be executed when a friend request is received. */
void callback_friendrequest(Friend_Requests *fr, void (*function)(uint8_t *, uint8_t *, uint16_t, void *),
                            void *userdata)
{
    fr->handle_friendrequest = function;
    fr->handle_friendrequest_isset = 1;
    fr->handle_friendrequest_userdata = userdata;
}
/* Set the function used to check if a friend request should be displayed to the user or not. */
void set_filter_function(Friend_Requests *fr, int (*function)(uint8_t *, void *), void *userdata)
{
    fr->filter_function = function;
    fr->filter_function_userdata = userdata;
}

/* Add to list of received friend requests. */
static void addto_receivedlist(Friend_Requests *fr, uint8_t *client_id)
{
    if (fr->received_requests_index >= MAX_RECEIVED_STORED)
        fr->received_requests_index = 0;

    id_copy(fr->received_requests[fr->received_requests_index], client_id);
    ++fr->received_requests_index;
}

/* Check if a friend request was already received.
 *
 *  return 0 if it did not.
 *  return 1 if it did.
 */
static int request_received(Friend_Requests *fr, uint8_t *client_id)
{
    uint32_t i;

    for (i = 0; i < MAX_RECEIVED_STORED; ++i)
        if (id_equal(fr->received_requests[i], client_id))
            return 1;

    return 0;
}


static int friendreq_handlepacket(void *object, uint8_t *source_pubkey, uint8_t *packet, uint32_t length)
{
    if (length == 0)
        return 1;

    ++packet;
    --length;

    Friend_Requests *fr = object;

    if (fr->handle_friendrequest_isset == 0)
        return 1;

    if (length <= sizeof(fr->nospam))
        return 1;

    if (request_received(fr, source_pubkey))
        return 1;

    if (memcmp(packet, &fr->nospam, sizeof(fr->nospam)) != 0)
        return 1;

    if (fr->filter_function)
        if ((*fr->filter_function)(source_pubkey, fr->filter_function_userdata) != 0)
            return 1;

    addto_receivedlist(fr, source_pubkey);

    packet[length - 1] = 0; /* Force NULL terminator. */

    (*fr->handle_friendrequest)(source_pubkey, packet + 4, length - 4, fr->handle_friendrequest_userdata);
    return 0;
}

void friendreq_init(Friend_Requests *fr, Onion_Client *onion_c)
{
    oniondata_registerhandler(onion_c, CRYPTO_PACKET_FRIEND_REQ, &friendreq_handlepacket, fr);
}
