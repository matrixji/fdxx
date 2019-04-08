#pragma once

namespace fdxx {
enum Event {
  none = 0x0000,
  read = 0x0001,
  write = 0x0002,
  accept = 0x0004,
  closed = 0x0008,
  error = 0x0010,
  all = 0xffff,
};
}
