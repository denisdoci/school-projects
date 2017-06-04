"""
resolve.py: a recursive resolver built using dnspython
"""

import argparse
import dns.message
import dns.name
import dns.query
import dns.rdata
import dns.rdataclass
import dns.rdatatype

# IMPORTANT NOTE !!!!!!
# Works for everything except
# an unglued server that encounters 2 CNAMES
# in the answers section
# i.e. www.yahoo.com.tw
# should work for yahoo.com.tw and
# all other CNAME queries

FORMATS = (("CNAME", "{alias} is an alias for {name}"),
           ("A", "{name} has address {address}"),
           ("AAAA", "{name} has IPv6 address {address}"),
           ("MX", "{name} mail is handled by {preference} {exchange}"))

# current as of 23 February 2017

ROOT_SERVERS = ("198.41.0.4",
                "192.228.79.201",
                "192.33.4.12",
                "199.7.91.13",
                "192.203.230.10",
                "192.5.5.241",
                "192.112.36.4",
                "198.97.190.53",
                "192.36.148.17",
                "192.58.128.30",
                "193.0.14.129",
                "199.7.83.42",
                "202.12.27.33")


#list of globals
CNAMERESTART = False
FOUNDIP = ''
CURRENT = ''

def collect_results(name: str, usedipaddresses) -> dict:

    """
    This function parses final answers into the proper data structure that
    print_results requires. The main work is done within the `lookup` function.
    """
    global FOUNDIP
    global CNAMERESTART
    global CURRENT

    CURRENT = name


    full_response = {}
    target_name = dns.name.from_text(name)

    # lookup A
    response = lookup(target_name, dns.rdatatype.A)
    arecords = []
    if len(response.answer) > 0:
        for answers in response.answer:
            a_name = answers.name
            for answer in answers:
                if answer.rdtype == 1:  # A record
                    arecords.append({"name": a_name, "address": str(answer)})

    # lookup CNAME
    response = lookup(target_name, dns.rdatatype.CNAME)
    cnames = []
    if len(response.answer) > 0:
        for answers in response.answer:
            for answer in answers:
                cnames.append({"name": answer, "alias": name})

    # lookup AAAA
    response = lookup(target_name, dns.rdatatype.AAAA)
    aaaarecords = []
    if len(response.answer) > 0:
        for answers in response.answer:
            aaaa_name = answers.name
            for answer in answers:
                if answer.rdtype == 28:  # AAAA record
                    aaaarecords.append(
                        {"name": aaaa_name, "address": str(answer)})

    # lookup MX
    response = lookup(target_name, dns.rdatatype.MX)
    mxrecords = []
    if len(response.answer) > 0:
        for answers in response.answer:
            mx_name = answers.name
            for answer in answers:
                if answer.rdtype == 15:  # MX record
                    mxrecords.append({"name": mx_name,
                                      "preference": answer.preference,
                                      "exchange": str(answer.exchange)})

    full_response["CNAME"] = cnames
    full_response["A"] = arecords
    full_response["AAAA"] = aaaarecords
    full_response["MX"] = mxrecords

    CNAMERESTART = False
    CURRENT = ''
    FOUNDIP = ''

    return full_response

def doanswersection(qtype: dns.rdata.Rdata, response):
    global CNAMERESTART
    for answers in response.answer:
        for answer in answers:
            try:
                if answer.rdtype == dns.rdatatype.CNAME:
                    if qtype == dns.rdatatype.CNAME:
                        return response
                    newlookupname = dns.name.from_text(str(answer))
                    CNAMERESTART = True
                    return lookup(newlookupname, qtype)
            
                elif answer.rdtype == dns.rdatatype.A:  # A record
                    return response

                else:
                    continue
            except:
                continue
    return response

def doadditionalsection(target_name: dns.name.Name,
            qtype: dns.rdata.Rdata, response):
    global FOUNDIP
    for additionals in response.additional:
        for a in additionals:
            try:
                if a.rdtype == dns.rdatatype.A:
                    ip = a.address
                    newquery = dns.message.make_query(target_name, qtype)
                    response = dns.query.udp(newquery, ip, 3)
                    if len(response.answer) > 0:
                        FOUNDIP = ip
                    return recursivesearch(target_name, qtype, response)
                else:
                    continue
            except:
                continue
    return response

def doauthoritysection(qtype: dns.rdata.Rdata, response):
    global CNAMERESTART
    for authorities in response.authority:
        for authority in authorities:
            try:
                target_name = dns.name.from_text(str(authority))
                CNAMERESTART = True
                lookup(target_name, qtype)
                outbound_query = dns.message.make_query(CURRENT, qtype)
                response = dns.query.udp(outbound_query, FOUNDIP, 3)
                CNAMERESTART = False
                return recursivesearch(CURRENT, qtype, response)
            except:
                continue
    return response

def recursivesearch(target_name: dns.name.Name,
            qtype: dns.rdata.Rdata, response):

    if len(response.answer) > 0:
        return doanswersection(qtype,response)

    elif len(response.additional) > 0:
        return doadditionalsection(target_name,qtype,response)

    elif len(response.authority)>0 and CNAMERESTART is False:
        return doauthoritysection(qtype,response)

    else:
        return response


def lookup(target_name: dns.name.Name,
           qtype: dns.rdata.Rdata) -> dns.message.Message:
    """
    This function uses a recursive resolver to find the relevant answer to the
    query.

    TODO: replace this implementation with one which asks the root servers
    and recurses to find the proper answer.
    """
    if qtype is not dns.rdatatype.A and CNAMERESTART is not True:
        outbound_query = dns.message.make_query(target_name, qtype)
        response = dns.query.udp(outbound_query, FOUNDIP, 3)
        return response

    outbound_query = dns.message.make_query(target_name, qtype)
    for server in ROOT_SERVERS:
        try:
            response = dns.query.udp(outbound_query, server, 3)
        except:
            continue
        returnresponse = recursivesearch(target_name, qtype, response)
        if type(response) is not None:
            break
    return returnresponse



def print_results(results: dict) -> None:
    """
    take the results of a `lookup` and print them to the screen like the host
    program would.
    """
    for rtype, fmt_str in FORMATS:
        for result in results.get(rtype, []):
            print(fmt_str.format(**result))


def simplecache(name, usedipaddresses):
    for ipandresponse in usedipaddresses:
        if ipandresponse[1] == name:
            return ipandresponse[0]
    return None

def main():
    """
    if run from the command line, take args and call
    printresults(lookup(hostname))
    """
    usedipaddresses = []
    argument_parser = argparse.ArgumentParser()
    argument_parser.add_argument("name", nargs="+",
                                 help="DNS name(s) to look up")
    argument_parser.add_argument("-v", "--verbose",
                                 help="increase output verbosity",
                                 action="store_true")
    program_args = argument_parser.parse_args()
    for a_domain_name in program_args.name:
        isincache = simplecache(a_domain_name, usedipaddresses)
        if isincache is not None:
            print_results(isincache)
        else:
            results = collect_results(a_domain_name, usedipaddresses)
            print_results(results)
            usedipaddresses.insert(0,(results,a_domain_name))

if __name__ == "__main__":
    main()


