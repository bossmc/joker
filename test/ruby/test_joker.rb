require 'bacon'
require 'joker'

describe 'A Wildcard' do

    before do
        @wild  ||= Wildcard['Fairy?ake*']
        @wildi ||= Wildcard['Fairy?ake*\?', true]
        @wildc ||= Wildcard['Fairy[cf]ake[!\\]]']
    end

    it 'should be constructed correctly' do
        @wild.casefold?.should.be.false
        @wildi.casefold?.should.be.true
        @wildc.casefold?.should.be.false
        regexp  = @wild.instance_variable_get(:@regexp)
        regexpi = @wildi.instance_variable_get(:@regexp)
        regexpc = @wildc.instance_variable_get(:@regexp)
        regexp.should.be  == /^Fairy.ake.*$/
        regexpi.should.be == /^Fairy.ake.*\?$/i
        regexpc.should.be == /^Fairy[cf]ake[!\]]$/
    end

    it 'should match correct strings' do
        @wild.should =~ 'Fairycake'
        @wild.should =~ 'Fairyfakes'
        @wild.should =~ 'Fairylake is a cool place'
    end

    it 'should not match incorrcet strings' do
        @wild.should.not =~ 'Dairycake'
        @wild.should.not =~ 'Fairysteakes'
        @wild.should.not =~ 'fairycake'
    end

    it 'should match case insensitive' do
        @wildi.should =~ 'FairyCake?'
        @wildi.should =~ 'fairyfakes?'
        @wildi.should =~ 'FairyLake IS A COOL Place?'
    end

    it 'should handle escapes correctly' do
        wild   = Wildcard['\\\\a\\?b\\*c\\d.][+']  # \\a\?b\*c\d.][+
        regexp = wild.instance_variable_get(:@regexp)
        regexp.should.be == /^\\a\?b\*c\\d\.\]\[\+$/
    end

    it 'should quote correctly' do
        Wildcard.quote('*?\\').should.be  == '\\*\\?\\\\'   # *?\  -->  \*\?\\
        Wildcard.quote('\\\\').should.be  == '\\\\\\\\'     # \\   -->  \\\\
    end

    it 'should know about character classes' do
        @wildc.should =~ 'Fairycake!'
        @wildc.should =~ 'Fairyfake]'
    end

end

