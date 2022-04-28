#include <unistd.h>
#include <cassert>
#include <optional>
#include <string>

#include "../../test_utils/test_utils.h"

using namespace std;

int main() {
  char hostnamebuf[256];
  gethostname(hostnamebuf, 256);
  string hostname(hostnamebuf);

  string shardmaster_addr = hostname + ":8080";
  start_shardmaster(shardmaster_addr);

  const string skv_1 = hostname + ":8081";
  const string skv_2 = hostname + ":8082";
  const string skv_3 = hostname + ":8083";

  start_shardkvs({skv_1, skv_2, skv_3}, shardmaster_addr);

  assert(test_join(shardmaster_addr, skv_1, true));
  assert(test_join(shardmaster_addr, skv_2, true));
  assert(test_join(shardmaster_addr, skv_3, true));

  // sleep to allow shardkvs to query and get initial config
  std::chrono::milliseconds timespan(1000);
  std::this_thread::sleep_for(timespan);

  assert(test_get(skv_1, "user_0", nullopt));
  assert(test_get(skv_2, "post_1", nullopt));
  assert(test_get(skv_3, "user_2", nullopt));

  assert(test_put(skv_1, "user_1", "Bob", "user_1", true));
  assert(test_put(skv_2, "post_500", "hello!", "user_1", true));
  assert(test_get(skv_1, "user_1_posts", "post_500,"));

  assert(test_get(skv_1, "user_1", "Bob"));
  assert(test_get(skv_2, "post_500", "hello!"));

  assert(test_get(skv_3, "user_1", nullopt));
  assert(test_get(skv_3, "post_500", nullopt));

  assert(test_delete(skv_2, "post_500", true));
  assert(test_get(skv_2, "post_500", nullopt));

  assert(test_delete(skv_1, "user_1", true));
  assert(test_get(skv_1, "user_1", nullopt));

  return 0;
}
