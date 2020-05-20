#!/bin/env perl

use strict;
use warnings;

my $target = shift @ARGV;

sub scan_dir {
    my $path = shift @_;

    print "Scanning $path";

    my @entries = <"$path/*">;

    my @dirs;
    my @files;

    foreach my $newpath (@entries) {
        if (-d $newpath) {
            scan_dir($newpath);
            if ($newpath =~ m!([^/]+)$!) {
                push @dirs, $1;
            }
        }
        elsif (-f $newpath) {
            if ($newpath =~ m!([^/]+)\.(?:c(?:pp))$!) {
                push @files, $1;
            }
        }
    }

    my @incl_dirs = map {"add_subdirectory(" . $_ . ")"} @dirs;

    print join("\n", @incl_dirs) . "\n";
    print "target_sources($target PRIVATE\n" . join("\n", @files) . "\n)\n";

    open my $CMAKE, '>', "$path/CMakeLists.txt";
    print $CMAKE join("\n", @incl_dirs) . "\n";
    print $CMAKE "target_sources($target PRIVATE\n" . join("\n", @files) . "\n)\n";
    close $CMAKE;
}

scan_dir("source");