Gem::Specification.new do |s|
  s.name = %q{joker}
  s.version = "1.1.0"

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["Fabian Streitel"]
  s.date = %q{2011-08-25}
  s.description = %q{Joker is a simple wildcard implementation that works much like Regexps}
  s.summary = %q{Joker is a simple wildcard implementation}
  s.email = %q{karottenreibe@gmail.com}
  s.license = %q{MIT}
  s.homepage = %q{http://karottenreibe.github.com/joker}
  s.require_paths = ["lib"]

  s.extensions = ["ext/joker_native/extconf.rb"]
  s.extra_rdoc_files = [
    "LICENSE.txt",
    "README.markdown"
  ]
  s.files = [
    "HISTORY.markdown",
    "LICENSE.txt",
    "README.markdown",
    "Rakefile",
    "VERSION",
    "ext/joker_native/Joker.c",
    "ext/joker_native/Joker.h",
    "ext/joker_native/Wildcard.c",
    "ext/joker_native/Wildcard.h",
    "ext/joker_native/compile.c",
    "ext/joker_native/compile.h",
    "ext/joker_native/extconf.rb",
    "ext/joker_native/match.c",
    "ext/joker_native/match.h",
    "lib/joker.rb",
    "test/c/test_compile.c",
    "test/c/test_match.c",
    "test/ruby/test_joker.rb"
  ]

  s.add_runtime_dependency("rake-compiler", "~> 0")
  s.add_runtime_dependency("rake", ">= 10", "< 14")
  s.add_runtime_dependency("bacon", "~> 1")
end

