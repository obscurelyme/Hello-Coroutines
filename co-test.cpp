#include <co/all.h>

void f() {
  while (true) {
    LOG << "s: " << co::scheduler_id() << " c: " << co::coroutine_id();
    co::sleep(3000);
  }
}

DEF_main(argc, argv) {
  flag::init(argc, argv);
  log::init();
  co::init();
  FLG_cout = true;

  co::Event ev;

  go([ev]() { ev.signal(); });

  ev.wait(100);

  // for (int i = 0; i < 32; i++) {
  //   go(f);
  // }

  // while (true) {
  //   sleep::sec(1024);
  // }

  // LOG << FLG_s;

  // go([]() { LOG << FLG_s; });

  return 0;
}
