#
# Joker is a simple Wildcard implementation that works much like Regexps.
#

class Wildcard

    attr_accessor :casefold
    attr_reader   :source

    def initialize( wildcard_string, casefold = true )
        @source = wildcard_string
        @casefold = casefold
        @regexp =
            if casefold then Regexp.new(compile, Regexps::IGNORECASE)
            else             Regexp.new(compile)
            end
    end

    class << self

        def quote( string )
            string.gsub(%r{[\\?*]}) { "\\#{$0}" }
        end

        alias_method :[], :new
        alias_method :compile, :new
        alias_method :escape, :quote

    end

    def inspect
        %{Wildcard[#{@wild.inspect}]#{@casefold ? 'i' : ''}}
    end

    def ~
        self =~ $_
    end

    def =~( string )
        @regexp =~ string
    end

    def ===( object )
        !!(self =~ object)
    end

    def eql?( that )
        @source == that.source && @casefold == that.casefold
    end

    alias_method :==, :eql?
    alias_method :casefold?, :casefold

    private

    def compile
        ptr = 0
        compiled = '^'
        while ptr < @source.length
            snip = @source[ptr..ptr]
            case snip
            when '\\'
                lookahead = @source[ptr+1..ptr+1]
                case snip
                when '\\\\', '\\?', '\\*'
                    compiled << snip << lookahead
                else
                    compiled << Regexp.quote(lookahead)
                end
                ptr += 1
            when '?' then compiled << '.'
            when '*' then compiled << '.*'
            else     then compiled << Regexp.quote(snip)
            end
            ptr += 1
        end
        compiled + '$'
    end

end

