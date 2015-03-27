require 'rake/extensiontask'
spec = Gem::Specification.load('joker.gemspec')
Rake::ExtensionTask.new('joker_native', spec)

require 'rake/testtask'
Rake::TestTask.new do |t|
  t.libs << "test"
  t.test_files = FileList['test/ruby/test*.rb']
  t.verbose = true
end

require 'rdoc/task'
RDoc::Task.new do |rdoc|
  rdoc.rdoc_dir = 'rdoc'
  rdoc.title = 'Joker'
  rdoc.rdoc_files.include('lib/**/*.rb')
  rdoc.rdoc_files.include('ext/**/*.c')
end
