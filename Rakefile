
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
end

Jeweler::RubyforgeTasks.new


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


CLEAN.include 'tmp/test'

desc('Test the ruby part of Joker')
task :test do
    sh 'bacon -Ilib test/ruby/test_*.rb'
end

