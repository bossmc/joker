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
    sh 'bacon -Ilib test/ruby/test_*.rb'
end

task :ctest_compile => [:compile] do
    sh 'mkdir -p tmp/test'
    sh 'cp test/c/* tmp/test'
    Dir.chdir('tmp/test')
    FileList['*.c'].each do |cfile|
        sh "gcc -I. -I../../ext/joker -I/usr/lib/ruby/1.8/i686-linux/ -c #{cfile}"
    end
    ofiles = FileList['../i686-linux/joker/1.8.7/*.o']
    FileList['*.o'].each do |ofile|
        sh "gcc -L. -L/usr/lib -lruby -lpthread -lcrypto -lcmockery #{ofiles} #{ofile} -o #{ofile.ext}"
    end
    Dir.chdir('../..')
end

task :ctest => [:ctest_compile] do
    FileList['tmp/test/*.o'].each do |cfile|
    puts '', '------------------------'
        sh "#{cfile.ext}"
    end
end

require 'rake/extensiontask'
Rake::ExtensionTask.new('joker', jeweler_tasks.gemspec) do |ext|
    ext.cross_compile = true
    ext.cross_platform = 'i386-mswin32'
end

