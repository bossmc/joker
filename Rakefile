require 'jeweler'

task :build => :gemspec

Jeweler::Tasks.new do |gem|
    gem.name = 'joker'
    gem.summary = gem.description =
        'Joker is a simple wildcard implementation that works much like Regexps'
    gem.email = 'karottenreibe@gmail.com'
    gem.homepage = 'http://karottenreibe.github.com/joker'
    gem.authors = ['Fabian Streitel']
    gem.rubyforge_project = 'k-gems'
end

Jeweler::RubyforgeTasks.new

task :test do
    sh 'bacon -Ilib test/test_*.rb'
end

