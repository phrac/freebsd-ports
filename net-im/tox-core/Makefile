# Created by: Derek Musselmann aka phrac <derek@disflux.com>
# $FreeBSD$

PORTNAME=	tox-core
PORTVERSION=	20140302
CATEGORIES=	net-im
MASTER_SITES=	GH

MAINTAINER=	derek@disflux.com
COMMENT=	A free as in freedom Skype replacement

LICENSE=	GPLv3

LIB_DEPENDS=	libsodium.so:${PORTSDIR}/security/libsodium

USE_LDCONFIG=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	irungentoo
GH_PROJECT=	ProjectTox-Core
GH_COMMIT=	de69dce
GH_TAGNAME=	${GH_COMMIT}

USE_AUTOTOOLS=	autoconf

pre-configure:
	@cd ${WRKSRC} && ${SH} autogen.sh

post-patch:
	@${REINPLACE_CMD} -e 's|(libdir)|{PREFIX}/libdata|g' ${WRKSRC}/Makefile.am

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/libtoxcore.so.0

.include <bsd.port.mk>
