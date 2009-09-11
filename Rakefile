require 'jeweler'

task :release do
    sh "vim HISTORY.markdown"
    sh "vim README.markdown"
    sh "git commit -a -m 'prerelease adjustments'; true"
end

jeweler_tasks = Jeweler::Tasks.new do |gem|
    gem.name = 'joker'
    gem.summary = gem.description =
        'Joker is a simple wildcard implementation that works much like Regexps'
    gem.email = 'karottenreibe@gmail.com'
    gem.homepage = 'http://github.com/karottenreibe/joker'
    gem.authors = ['Fabian Streitel']
    gem.rubyforge_project = 'k-gems'
end

Jeweler::RubyforgeTasks.new

require 'rake/rdoctask'
Rake::RDocTask.new do |rdoc|
  rdoc.rdoc_dir = 'rdoc'
  rdoc.title = 'Joker'
  rdoc.rdoc_files.include('lib/*.rb')
end

task :test do
    sh 'bacon -Ilib test/test_*.rb'
end

require 'rake/extensiontask'
Rake::ExtensionTask.new('joker', jeweler_tasks.gemspec) do |ext|
    ext.cross_compile = true
    ext.cross_platform = 'i386-mswin32'
end

