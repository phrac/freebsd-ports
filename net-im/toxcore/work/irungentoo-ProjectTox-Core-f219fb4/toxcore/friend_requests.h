/* friend_requests.h
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

#ifndef FRIEND_REQUESTS_H
#define FRIEND_REQUESTS_H

#include "onion_client.h"
#include "net_crypto.h"


typedef struct {
    uint32_t nospam;
    void (*handle_friendrequest)(uint8_t *, uint8_t *, uint16_t, void *);
    uint8_t handle_friendrequest_isset;
    void *handle_friendrequest_userdata;

    int (*filter_function)(uint8_t *, void *);
    void *filter_function_userdata;
    /* NOTE: The following is just a temporary fix for the multiple friend requests received at the same time problem.
     *  TODO: Make this better (This will most likely tie in with the way we will handle spam.)
     */

#define MAX_RECEIVED_STORED 32

    uint8_t received_requests[MAX_RECEIVED_STORED][crypto_box_PUBLICKEYBYTES];
    uint16_t received_requests_index;
} Friend_Requests;

/* Try to send a friendrequest to peer with public_key.
 *  data is the data in the request and length is the length.
 */
int send_friendrequest(Onion_Client *onion_c, uint8_t *public_key, uint32_t nospam_num, uint8_t *data, uint32_t length);
/* Set and get the nospam variable used to prevent one type of friend request spam. */
void set_nospam(Friend_Requests *fr, uint32_t num);
uint32_t get_nospam(Friend_Requests *fr);

/* Set the function that will be executed when a friend request for us is received.
 *  Function format is function(uint8_t * public_key, uint8_t * data, uint16_t length, void * userdata)
 */
void callback_friendrequest(Friend_Requests *fr, void (*function)(uint8_t *, uint8_t *, uint16_t, void *),
                            void *userdata);

/* Set the function used to check if a friend request should be displayed to the user or not.
 * Function format is int function(uint8_t * public_key, void * userdata)
 * It must return 0 if the request is ok (anything else if it is bad.)
 */
void set_filter_function(Friend_Requests *fr, int (*function)(uint8_t *, void *), void *userdata);

/* Sets up friendreq packet handlers. */
void friendreq_init(Friend_Requests *fr, Onion_Client *onion_c);


#endif
