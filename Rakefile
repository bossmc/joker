
task :release do
    sh "vim HISTORY.markdown"
    sh "vim README.markdown"
    sh "git commit -a -m 'prerelease adjustments'; true"
end

require 'jeweler'
jeweler_tasks = Jeweler::Tasks.new do |gem|
    gem.name                = 'joker'
    gem.summary             = 'Joker is a simple wildcard implementation that works much like Regexps'
    gem.description         = gem.summary
    gem.email               = 'karottenreibe@gmail.com'
    gem.homepage            = 'http://github.com/karottenreibe/joker'
    gem.authors             = ['Fabian Streitel']
    gem.rubyforge_project   = 'k-gems'

    gem.files.include('lib/joker_native.*') # add native stuff
end

Jeweler::RubyforgeTasks.new
Jeweler::GemcutterTasks.new


require 'rake/rdoctask'
Rake::RDocTask.new do |rdoc|
    rdoc.rdoc_dir = 'rdoc'
    rdoc.title = 'Joker'
    rdoc.rdoc_files.include('lib/**/*.rb')
    rdoc.rdoc_files.include('ext/**/*.rb')
end


require 'rake/extensiontask'
require 'rake/extensiontesttask'
Rake::ExtensionTask.new('joker_native', jeweler_tasks.gemspec) do |ext|
    ext.cross_compile   = true
    ext.cross_platform  = 'i386-mswin32'
    ext.test_files      = FileList['test/c/*']
end


# workaround for rake-compiler which needs the gemspec to have a
# version and yaml-dump-loads the
# gemspec which leads to errors since procs can't be loaded
Rake::Task.tasks.each do |task|
    if task.to_s.start_with?('native')
        task.prerequisites.unshift(:gemspec, :fix_rake_compiler_gemspec_dump)
    end
end
task :fix_rake_compiler_gemspec_dump do
    %w{files extra_rdoc_files test_files}.each do |accessor|
        jeweler_tasks.gemspec.send(accessor).instance_eval { @exclude_procs = Array.new }
    end
end


CLEAN.include 'lib/*.so'

desc('Test the ruby part of Joker')
task :test do
    sh 'bacon -Ilib test/ruby/test_*.rb'
end

