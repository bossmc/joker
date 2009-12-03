require 'rake/extensiontask'
require 'rake/extensiontesttask'

Rake::ExtensionTask.new('joker_native', $gemspec) do |ext|
    ext.cross_compile   = true
    ext.cross_platform  = 'x86-mswin32'
    ext.test_files      = FileList['test/c/*']
end

CLEAN.include 'lib/**/*.so'


# Workaround for rake-compiler, which YAML-dump-loads the
# gemspec, which leads to errors since Procs can't be loaded
Rake::Task.tasks.each do |task_name|
    case task_name.to_s
    when /^native/
        task_name.prerequisites.unshift("fix_rake_compiler_gemspec_dump")
    end
end

task :fix_rake_compiler_gemspec_dump do
    %w{files extra_rdoc_files test_files}.each do |accessor|
        $gemspec.send(accessor).instance_eval { @exclude_procs = Array.new }
    end
end

