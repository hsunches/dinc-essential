#!/usr/bin/perl
use strict;

my $header = $ARGV[0];
my $fh;

open $fh, $header || die "Can't found $header";

my @lines = <$fh>;

close($fh);

my %cat_hash;

foreach (@lines) {
	if (/\#define (HAL_\w+)\s+(\d+)/) {
		$cat_hash{$1} = $2;
	}
}

my $content = join("\n", @lines);

$content =~ s/[\t\n]//g;

my %id_hash;

foreach my $key (keys %cat_hash) {
	my $type_name = lc $key."_msg_type";

	next if ($content !~ /$type_name\{(.+)\} $type_name/);

	my @enums = split(",", $1);
	my $value = $cat_hash{$key};

	foreach (@enums) {
		s/ = $key//;
		$id_hash{$value++} = $_;
	}
}

foreach (sort keys %id_hash) {
	print "[$_]\n";
	print "name=$id_hash{$_}\n";
	print "type=fixed\n";
	print "value=null\n\n";
}
