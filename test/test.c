#include "../include/swim.h"

int main(void) {
  WindowListOptions options = {
    .exclude_desktop_elements = true,
    .on_screen_only = true,
  };

  WindowList window_list = get_window_list(options, NULL);

  for (int i = 0; i < window_list.count; i++) {
    window *w = window_list.windows[i];
    CFStringRef cf_title = get_window_title(w);
    char *title = cstring_from_CFString(cf_title);
    printf("%d: %s\n", i, title);
    free(title);
    destroy_window(w);
  }
}
