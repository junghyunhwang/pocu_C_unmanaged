#include <stdio.h>
#include "cyber_spaceship.h"

int main(void)
{
    const char cyber_asteroid_belt[30]; /* 총 구역 */
    const char* cluster_start_addresses[2]; /* 소행성 지대들의 시작 주소 */
    size_t cluster_lengths[2]; /* 각 소행성의 길이 */
    size_t out_longest_safe_area_length = 0; /* 가장 긴 안전구역 길이 */
    size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length; /* 가장 긴 안정구역 길이 메모리의 주소 */
    const char* longest_safe_cluster_start_address; /* 리턴 값 */

    const char* cluster1 = &cyber_asteroid_belt[12];
    const char* cluster2 = &cyber_asteroid_belt[3];

    cluster_start_addresses[0] = cluster1;
    cluster_start_addresses[1] = cluster2;

    cluster_lengths[0] = 15U;
    cluster_lengths[1] = 25U;

    
    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, 30, cluster_start_addresses, cluster_lengths, 6, out_longest_safe_area_length_p); /* longest_safe_cluster_start_address: (cyber_asteroid_belt + 12), out_longest_safe_area_length: 15 */

    printf("cyber_asteroid_belt address: %p\n", (void*)cyber_asteroid_belt);
    printf("=======================\n");
    printf("expected address: %p\n", (void*)&cyber_asteroid_belt[12]);
    printf("result address: %p\n", (void*)longest_safe_cluster_start_address);
    printf("expected Longest length value: %d\n", 15);
    printf("result Longest length value: %d\n", out_longest_safe_area_length);

    return 0;
}
