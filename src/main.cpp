import std;

import Constants;
import ArgsParser;
import GameProcess;
import Error;
import DeathCounterRenderer;
import Win32Utils;

using namespace std::literals;

auto main(int argc, char **argv) noexcept -> int {
  setThreadLangID();
  
  auto args = std::vector<std::string_view> {};
  args.reserve(argc);

  for (auto i = 0; i < argc; ++i) args.emplace_back(argv[i]);

  return parseArgs(args)
    .and_then([](auto disable_overlay) noexcept -> decltype(auto) {
                 std::println("Looking for FromSoftware game process...");
                 return findProcess(disable_overlay);
               })
    .and_then([](auto &&ctx) noexcept -> decltype(auto) {
                 std::println("Process {} {} bit found! pid: {}\n", ctx.name, ctx.bit_count, ctx.pid);
                 std::println("Opening process handle...");
                 return openProcessHandle(std::move(ctx));
                })
    .and_then([](auto &&ctx) noexcept -> decltype(auto) {
                 std::println("Process handle successfully opened!\n");
                 return renderDeathCounter(std::move(ctx));
                })
    .transform_error([](auto &&error) noexcept -> int {
                 std::println("{}", error.description);
                 if(error.show_help)
                     std::println("{}", HELP_STRING);

                 return -1;
             })
    .value();
}
