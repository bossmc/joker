
desc("Build linux and windows specific gems")
task :gems do
    sh "rake build:native"
    sh "rake build:cross"
end

task "build:native" => [:native, :build] do
    file = "pkg/joker-#{`cat VERSION`.chomp}.gem"
    mv file, "#{file.ext}-x86-linux.gem"
end

task "build:cross" => [:cross, :native, :build] do
    file = "pkg/joker-#{`cat VERSION`.chomp}.gem"
    mv file, "#{file.ext}-x86-mingw32.gem"
end

