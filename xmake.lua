package("frozen2", function()
    set_kind("library", { moduleonly = true })
    set_homepage("https://github.com/Arthapz/frozen")
    set_description("A header-only, constexpr alternative to gperf for C++14 users")
    set_license("Apache-2.0")

    set_urls("https://github.com/Arthapz/frozen.git")

    add_configs("modules", { default = false, type = "boolean" })

    on_install(function(package)
          local configs = {
              modules = package:config("modules"),
          }
          import("package.tools.xmake").install(package, configs)
    end)
end)

add_defines("FROZEN_USE_STD_MODULE")
add_requireconfs("*", { configs = { modules = true, std_import = true } })
add_requires("frozen2")

target("fsdeathcounter")
    set_kind("binary")
    add_languages("c++latest")
    add_files("src/*.cpp", "src/*.mpp")
    add_syslinks("user32", "gdi32")
    add_packages("frozen2")
